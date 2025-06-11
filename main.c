#include "pico/stdlib.h"
#include "tusb.h"
#include "bsp/board.h"
#include "class/hid/hid.h"
#include "keyboard.h"
#include "ducky_parser.h"
#include "shd_sync.h"
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

 semaphore_t init_comp;    // semaphore for initialization. core1 task only launches after initialization is complete

int main() {
    board_init();
    tusb_init();

    sem_init(&init_comp, 0, 1);             // Lock start
    keyboard_init();
    multicore_launch_core1(testScript);
    sem_release(&init_comp);                // Lock release

    while (1) {
        tud_task();    
        keyboard_task();
    }

    return 0;
}
