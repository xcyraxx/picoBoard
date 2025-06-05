#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "tud_hid_keyboard.h"

int main(void) {
    board_init();
    tusb_init();
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    bool sent = false;

    while (1) {
        tud_task();

        if (tud_hid_ready() && !sent) {
            // Send a string as keyboard input
            send_key(HID_KEY_R, MOD_GUI);
            sleep_ms(1000);  // Wait for the key to be processed
            // //type notepad.exe and press enter
            send_string_as_keyboard("cmd.exe\n");
            sent = true;    
            sleep_ms(1600); // Wait for the command to be processed
            gpio_put(LED_PIN, 1); // Turn on the LED to indicate success
            send_string_as_keyboard("whoami\n");
            send_key(HID_KEY_ENTER, MOD_NONE);
        }
    }
}
