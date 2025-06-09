#include "pico/stdlib.h"
#include "tusb.h"
#include "bsp/board.h"
#include "class/hid/hid.h"
#include "keyboard.h"
#include "testScript.h"
#include "pico/multicore.h"

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, uint8_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)bufsize;
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    // Just return 0 if unused
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;
    return 0;
}

int main() {
    board_init();
    tusb_init();
    keyboard_init();
    multicore_launch_core1(testScript);

    while (1) {
        tud_task();    
        keyboard_task();
    }

    return 0;
}
