#include "testScript.h"
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"


static const char *script =
    "GUI r\n"
    "DELAY 500\n"
    "STRING Notepad.exe\n"
    "ENTER\n"
    "DELAY 1000\n"
    "STRING wassup cuh\n";


void parse_duckyscript(const char *script) {
    if (script == NULL) return;

    char *script_copy = strdup(script);
    if (!script_copy) return;

    char *saveptr;
    char *line = strtok_r(script_copy, "\n", &saveptr);
    while (line != NULL) {
        // Skip leading whitespace
        while (*line == ' ' || *line == '\t') line++;

        // Ignore empty lines
        if (*line == '\0') {
            line = strtok_r(NULL, "\n", &saveptr);
            continue;
        }

        // Handle REM (comment)
        if (strncmp(line, "REM", 3) == 0) {
            // Do nothing for comments
        }
        else if (strncmp(line, "DELAY ", 6) == 0) {
            char *delay_str = line + 6;
            while (*delay_str == ' ' || *delay_str == '\t') delay_str++;
            int ms = atoi(delay_str);
            if (ms > 0) {
                sleep_ms((uint32_t)ms);
            }
        }
        else if (strncmp(line, "STRING ", 7) == 0) {
            const char *str = line + 7;
            reportQueue *q = get_keyboard_queue();
            while (*str) {
                uint8_t keycode = 0;
                switch (*str) {
                    case 'A' ... 'Z':
                        keycode = HID_KEY_A + (*str - 'A');
                        break;
                    case 'a' ... 'z':
                        keycode = HID_KEY_A + (*str - 'a');
                        break;
                    case '0':
                        keycode = HID_KEY_0;
                        break;
                    case '1':
                        keycode = HID_KEY_1;
                        break;
                    case '2':
                        keycode = HID_KEY_2;
                        break;
                    case '3':
                        keycode = HID_KEY_3;
                        break;
                    case '4':
                        keycode = HID_KEY_4;
                        break;
                    case '5':
                        keycode = HID_KEY_5;
                        break;
                    case '6':
                        keycode = HID_KEY_6;
                        break;
                    case '7':
                        keycode = HID_KEY_7;
                        break;
                    case '8':
                        keycode = HID_KEY_8;
                        break;
                    case '9':
                        keycode = HID_KEY_9;
                        break;
                    case ' ':
                        keycode = HID_KEY_SPACE;
                        break;
                    case '\t':
                        keycode = HID_KEY_TAB;
                        break;
                    case '\n': 
                        keycode = HID_KEY_ENTER;
                        break;
                    case '-':
                        keycode = HID_KEY_MINUS;
                        break;
                    case '=':
                        keycode = HID_KEY_EQUAL;
                        break;
                    case '[':
                        keycode = HID_KEY_LEFT_BRACKET;
                        break;
                    case ']':
                        keycode = HID_KEY_RIGHT_BRACKET;
                        break;
                    case '\\':
                        keycode = HID_KEY_BACKSLASH;
                        break;
                    case ';':
                        keycode = HID_KEY_SEMICOLON;
                        break;
                    case '\'':
                        keycode = HID_KEY_APOSTROPHE;
                        break;
                    case ',':
                        keycode = HID_KEY_COMMA;
                        break;
                    case '.':
                        keycode = HID_KEY_DOT;
                        break;
                    case '/':
                        keycode = HID_KEY_SLASH;
                        break;
                    case '!':
                        keycode = HID_KEY_EXCLAMATION; // Assuming '!' is mapped to 1
                        break;
                    default:
                        keycode = 0;
                        break;
                }
                if (keycode) {
                    enqueue_report(q, &(report_t){.keycode = {keycode}});
                }
                str++;
            }
        } else if (strncmp(line, "GUI", 3) == 0) {
            // WIN KEY
            char *key = line + 3;
            while (*key == ' ' || *key == '\t') key++;
           //check which letter comes after GUI in one line and press
            reportQueue *q = get_keyboard_queue();
            uint8_t keycode = 0;
            if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }
            if (keycode) {
                enqueue_report(q, &(report_t){.modifier = MOD_LGUI, .keycode = {keycode}});
            }
        } else if (strncmp(line, "ENTER", 5) == 0) {
            // Handle ENTER key
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.keycode = {HID_KEY_ENTER}});
        } else if (strncmp(line, "ESC", 3) == 0) {
            // Handle ESC key
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.keycode = {HID_KEY_ESC}});
        } else if (strncmp(line, "BACKSPACE", 9) == 0) {
            // Handle BACKSPACE key
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.keycode = {HID_KEY_BACKSPACE}});
        } else if (strncmp(line, "TAB", 3) == 0) {
            // Handle TAB key
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.keycode = {HID_KEY_TAB}});
        }
        else if (strncmp(line, "CTRL", 4) == 0) {
            // Handle CTRL key
            char *key = line + 4;
            while (*key == ' ' || *key == '\t') key++;
            reportQueue *q = get_keyboard_queue();
            uint8_t keycode = 0;
            if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }
            if (keycode) {
                enqueue_report(q, &(report_t){.modifier = MOD_LCTRL, .keycode = {keycode}});
            }
        }
        else if (strncmp(line, "SHIFT", 5) == 0) {
            // Handle SHIFT key
            char *key = line + 5;
            while (*key == ' ' || *key == '\t') key++;
            reportQueue *q = get_keyboard_queue();
            uint8_t keycode = 0;
            if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }
            if (keycode) {
                enqueue_report(q, &(report_t){.modifier = MOD_LSHIFT, .keycode = {keycode}});
            }
        }
        else if (strncmp(line, "ALT", 3) == 0) {
            // Handle ALT key
            char *key = line + 3;
            while (*key == ' ' || *key == '\t') key++;
            reportQueue *q = get_keyboard_queue();
            uint8_t keycode = 0;
            if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }
            if (keycode) {
                enqueue_report(q, &(report_t){.modifier = MOD_LALT, .keycode = {keycode}});
            }
        }
        else if (strncmp(line, "CTRL-ALT", 8) == 0) {
            // Handle CTRL-ALT key combination
            char *key = line + 8;
            while (*key == ' ' || *key == '\t') key++;
            reportQueue *q = get_keyboard_queue();
            uint8_t keycode = 0;
            if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }
            if (keycode) {
                enqueue_report(q, &(report_t){.modifier = MOD_LCTRL | MOD_LALT, .keycode = {keycode}});
            }
        }
        else {
            // placeholder for unrecognized commands
        }
        // Next line
        line = strtok_r(NULL, "\n", &saveptr);
    }
    free(script_copy);
}

void testScript(){
    reportQueue *q = get_keyboard_queue();
    parse_duckyscript(script);
    // enqueue_report(q, &(report_t){.keycode = {HID_KEY_A}});
}

