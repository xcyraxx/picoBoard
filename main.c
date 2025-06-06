#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
//#include "tud_hid_keyboard.h"

int main(void) {
    board_init();
    tusb_init();
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

  //  bool sent = false;

    while (1) {
        tud_task();
        gpio_put(LED_PIN, 1); // Turn on the LED to indicate success
    }
}
