#ifndef _TUD_HID_KEYBOARD_H_
#define _TUD_HID_KEYBOARD_H_

#include "bsp/board.h"
#include "tusb.h"
#include "class/hid/hid.h"

#define MOD_NONE 0
#define MOD_GUI  (1 << 3)
#define MOD_SHIFT (1 << 1)
#define HID_KEY_DOT 0x37

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id,
                               hid_report_type_t report_type,
                               uint8_t* buffer, uint16_t reqlen) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id,
                           hid_report_type_t report_type,
                           uint8_t const* buffer, uint16_t bufsize) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)bufsize;
}

static void send_key(uint8_t keycode, uint8_t modifier) {
    uint8_t keycodes[6] = {0};
    keycodes[0] = keycode;

    // Wait until ready and send key down
    while (!tud_hid_ready()) tud_task();
    while (!tud_hid_keyboard_report(0, modifier, keycodes)) tud_task();
    sleep_ms(10);

    // Send key up (release)
    keycodes[0] = 0;
    while (!tud_hid_keyboard_report(0, 0, keycodes)) tud_task();
    sleep_ms(10);
}

static void send_string_as_keyboard(const char *str) {
    while (*str) {
        char c = *str++;
        uint8_t mod = MOD_NONE;
        uint8_t code = HID_KEY_NONE;

        if (c >= 'a' && c <= 'z') {
            code = HID_KEY_A + (c - 'a');
        } else if (c >= 'A' && c <= 'Z') {
            code = HID_KEY_A + (c - 'A');
            mod = MOD_SHIFT;
        } else if (c == ' ') {
            code = HID_KEY_SPACE;
        } else if (c == '\n') {
            code = HID_KEY_ENTER;
        }
          else if (c == '\t') {
            code = HID_KEY_TAB;
        } else if (c == '\\') {
            code = HID_KEY_BACKSLASH;
        } else if (c == '/') {
            code = HID_KEY_SLASH;
        } else if (c == '-') {
            code = HID_KEY_MINUS;
        } else if (c == '_') {
            code = HID_KEY_MINUS;
            mod = MOD_SHIFT;
        } else if (c == '=') {
            code = HID_KEY_EQUAL;
        } else if (c == '+') {
            code = HID_KEY_EQUAL;
            mod = MOD_SHIFT;
        } else if (c == '.') {
            code = HID_KEY_DOT;
        } else if (c == ',') {
            code = HID_KEY_COMMA;
        } else if (c == ';') {
            code = HID_KEY_SEMICOLON;
        }

         // If we have a valid keycode, send it
        if (code == HID_KEY_NONE) {
            // If the character is not supported, skip it
            continue;
        }
        if (code != HID_KEY_NONE) send_key(code, mod);
    }
}
#endif
