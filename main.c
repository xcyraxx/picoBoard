#include "pico/stdlib.h"
#include "tusb.h"
#include "bsp/board.h"
#include "class/hid/hid.h"
#include "keyboard.h"
#include "ducky_parser.h"
#include "shd_sync.h"
#include "pico/multicore.h"
#include <stdio.h>
#include "hardware/i2c.h"
#include "ssd1306.h"
#include <stdlib.h>
#include "payloads.h"
#include "ui.h"

#define I2C_PORT i2c0
#define SDA_PIN 0
#define SCL_PIN 1
#define OLED_ADDR 0x3C
#define BTN_SELECT 8

int selected;

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
    multicore_launch_core1(entry);
    sem_release(&init_comp);                // Lock release
    stdio_init_all();

   //Init BUTTON
    init_buttons();
    // Init I2C
    stdio_init_all();

    // I2C Init
    i2c_init(I2C_PORT, 100 * 1000);  // 100 kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // OLED config
    ssd1306_t oled;
    oled.external_vcc = false;
    if (!ssd1306_init(&oled, 128, 64, OLED_ADDR, I2C_PORT)) {
    printf("OLED init failed!\n");
    while (1) sleep_ms(1000);
}
    selected = select_payload_menu(&oled, payload_filenames, payload_count);

    // After selection, run the payload
    ssd1306_clear(&oled);
    ssd1306_draw_string(&oled, 0, 0, 2, "Selected!");
    ssd1306_draw_string(&oled, 0, 32, 1, payload_filenames[selected]);
    ssd1306_show(&oled);
    sleep_ms(2000);  // Show selection for a while
    ssd1306_clear(&oled);
    ssd1306_draw_string(&oled, 0, 0, 2, "Running payload:");
    ssd1306_draw_string(&oled, 0, 32, 2, payload_filenames[selected]);
    ssd1306_show(&oled);
    

    while (1) {
        tud_task();    
        keyboard_task();
    }

    return 0;
}
