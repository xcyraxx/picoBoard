#include "ducky_parser.h"
#include "pico/stdlib.h"



//Create a payload, rebuild project and then compile

void parse_duckyscript(const char *script) {
    if (script == NULL) return;

    char *script_copy = strdup(script);                 // Copy the script
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

        //-------------------------------------------
        //  Keyword - DELAY
        //-------------------------------------------
        else if (strncmp(line, "DELAY ", 6) == 0) {
            char *delay_str = line + 6;
            while (*delay_str == ' ' || *delay_str == '\t') delay_str++;
            int ms = atoi(delay_str);
            if (ms > 0) {
                reportQueue *q = get_keyboard_queue();
                report_t r = {0};
                r.cmd = CMD_DELAY;
                r.delay_ms = ms;
                enqueue_report(q, &r);
            }
        }

        //-------------------------------------------
        //  Keyword - STRING
        //-------------------------------------------
        else if (strncmp(line, "STRING ", 7) == 0) {
            const char *str = line + 7;
            reportQueue *q = get_keyboard_queue();
            while (*str) {
                int8 keycode = 0;
                int8 modifier = 0;
                switch (*str) {
                    case 'A' ... 'Z':
                        keycode = HID_KEY_A + (*str - 'A');
                        modifier = MOD_LSHIFT;
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
                        modifier = MOD_LSHIFT;
                        break;
                    default:
                        keycode = 0;
                        break;
                }
                if (keycode) {
                    enqueue_report(q, &(report_t){.cmd=CMD_KEY,.data._key.modifier = modifier, .data._key.keycode = {keycode}});
                }
                str++;
            }
        } 

        //-------------------------------------------
        //  Keyword - GUI
        //-------------------------------------------        
        else if (strncmp(line, "GUI", 3) == 0) {
            // WIN KEY
            char *key = line + 3;
            while (*key == ' ' || *key == '\t') key++;
            reportQueue *q = get_keyboard_queue();
            int8 keycode = 0;

            if (*key == '\0' || strcasecmp(key, "ENTER") == 0) {
                // Support for "GUI" alone or "GUI ENTER"
                keycode = HID_KEY_ENTER;
            } else if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }
            if (keycode) {
                report_t r = {0};
                r.cmd = CMD_KEY;
                r.data._key.modifier = MOD_LGUI;
                r.data._key.keycode[0] = keycode;
                enqueue_report(q, &r);
            }
        }
 
        //-------------------------------------------
        //  Keyword - ENTER
        //-------------------------------------------         
        
        else if (strncmp(line, "ENTER", 5) == 0) {
            // Handle ENTER key
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_ENTER}});
        } 

        //-------------------------------------------
        //  Keyword - ESC
        //-------------------------------------------         

        else if (strncmp(line, "ESC", 3) == 0) {
            // Handle ESC key
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_ESC}});
        } 
        
        //-------------------------------------------
        //  Keyword - BACKSPACE
        //-------------------------------------------         
         
        else if (strncmp(line, "BACKSPACE", 9) == 0) {
            // Handle BACKSPACE key
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_BACKSPACE}});
        } 

        //-------------------------------------------
        //  Keyword - TAB
        //-------------------------------------------         

        else if (strncmp(line, "TAB", 3) == 0) {
            // Handle TAB key
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_TAB}});
        }
        
        //-------------------------------------------
        //  Keyword - CTRL
        //-------------------------------------------         

        else if (strncmp(line, "CTRL", 4) == 0) {
            // Handle CTRL key
            char *key = line + 4;
            while (*key == ' ' || *key == '\t') key++;

            reportQueue *q = get_keyboard_queue();
            int8 keycode = 0;
            if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }

            if (keycode) {
                report_t r = {0};
                r.cmd = CMD_KEY;
                r.data._key.modifier = MOD_LCTRL;
                r.data._key.keycode[0] = keycode;
                enqueue_report(q, &r);
            }
        }
        
        //-------------------------------------------
        //  Keyword - SHIFT
        //-------------------------------------------         

        else if (strncmp(line, "SHIFT", 5) == 0) {
            // Handle SHIFT key
            char *key = line + 5;
            while (*key == ' ' || *key == '\t') key++;

            reportQueue *q = get_keyboard_queue();
            int8 keycode = 0;
            
            if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }
            
            if (keycode) {
                report_t r = {0};
                r.cmd = CMD_KEY;
                r.data._key.modifier = MOD_LSHIFT;
                r.data._key.keycode[0] = keycode;
                enqueue_report(q, &r);
            }
        }

        //-------------------------------------------
        //  Keyword - ALT
        //-------------------------------------------         

        else if (strncmp(line, "ALT", 3) == 0) {
            // Handle ALT key
            char *key = line + 3;
            while (*key == ' ' || *key == '\t') key++;

            reportQueue *q = get_keyboard_queue();
            int8 keycode = 0;

            if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }

            if (keycode) {
                report_t r = {0};
                r.cmd = CMD_KEY;
                r.data._key.modifier = MOD_LALT;
                r.data._key.keycode[0] = keycode;
                enqueue_report(q, &r);
            }
        }

        //-------------------------------------------
        //  Keyword - CTRL-ALT
        //-------------------------------------------         
 
        else if (strncmp(line, "CTRL-ALT", 8) == 0) {
            // Handle CTRL-ALT key combination
            char *key = line + 8;
            while (*key == ' ' || *key == '\t') key++;

            reportQueue *q = get_keyboard_queue();
            int8 keycode = 0;

            if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }

            if (keycode) {
                report_t r = {0};
                r.cmd = CMD_KEY;
                r.data._key.modifier = MOD_LCTRL | MOD_LALT ;
                r.data._key.keycode[0] = keycode;
                 
                enqueue_report(q, &r);
            }
        }
        else if (strncmp(line, "CMD KEY", 7) == 0) {
            // Handle CMD KEY
            char *key = line + 7;
            while (*key == ' ' || *key == '\t') key++;

            reportQueue *q = get_keyboard_queue();
            int8 keycode = 0;

            if (*key >= 'A' && *key <= 'Z') {
                keycode = HID_KEY_A + (*key - 'A');
            } else if (*key >= 'a' && *key <= 'z') {
                keycode = HID_KEY_A + (*key - 'a');
            } else {
                keycode = 0; // Unknown key
            }

            if (keycode) {
                report_t r = {0};
                r.cmd = CMD_KEY;
                r.data._key.modifier = MOD_LGUI;
                r.data._key.keycode[0] = keycode;
                enqueue_report(q, &r);
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
    sem_acquire_blocking(&init_comp);       // wait for initialization to complete

    reportQueue *q = get_keyboard_queue();
    parse_duckyscript(payloads[0]);
    parse_duckyscript(payloads[1]);
}

