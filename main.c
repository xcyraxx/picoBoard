#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "class/hid/hid.h"

void tud_hid_set_report_cb(uint8_t report_id, uint8_t report_type,
                           uint8_t const* buffer, uint16_t bufsize) {
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)bufsize;
}

uint16_t tud_hid_get_report_cb(uint8_t report_id, hid_report_type_t report_type,
                               uint8_t* buffer, uint16_t reqlen) {
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;
    return 0;
}

int main(void) {
    board_init();
    tusb_init();

    while (1) {
        tud_task();
    }
}
