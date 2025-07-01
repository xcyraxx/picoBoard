#include "ssd1306.h"
#include "ui.h"
#include <stdio.h>



void init_buttons() {
    gpio_init(BTN_UP);     gpio_set_dir(BTN_UP, GPIO_IN);     gpio_pull_up(BTN_UP);
    gpio_init(BTN_DOWN);   gpio_set_dir(BTN_DOWN, GPIO_IN);   gpio_pull_up(BTN_DOWN);
    gpio_init(BTN_SELECT); gpio_set_dir(BTN_SELECT, GPIO_IN); gpio_pull_up(BTN_SELECT);
}

int select_payload_menu(ssd1306_t *oled, const char **items, int count) {
    int top = 0;

    while (true) {
        // === Draw screen ===
        ssd1306_clear(oled);
        for (int i = 0; i < 3; i++) {
            int index = top + i;
            if (index >= count) break;

            char line[22];
            snprintf(line, sizeof(line), "%c %s", (index == selected) ? '>' : ' ', items[index]);
            ssd1306_draw_string(oled, 0, i * 16, 2, line);
        }
        ssd1306_show(oled);

        // === Handle input ===
        if (gpio_get(BTN_UP) == 0) {
            if (selected > 0) selected--;
            if (selected < top) top--;
            sleep_ms(200);
        }

        if (gpio_get(BTN_DOWN) == 0) {
            if (selected < count - 1) selected++;
            if (selected >= top + 3) top++;
            sleep_ms(200);
        }

        if (gpio_get(BTN_SELECT) == 0) {
            // Wait for release
            while (gpio_get(BTN_SELECT) == 0) sleep_ms(10);
            return selected;
        }

        sleep_ms(50);
    }
}
