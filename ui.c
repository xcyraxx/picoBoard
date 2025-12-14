#include "ssd1306.h"
#include "ui.h"
#include <stdio.h>
#include "tusb.h"

void init_buttons() {
    gpio_init(BTN_UP);     gpio_set_dir(BTN_UP, GPIO_IN);     gpio_pull_up(BTN_UP);
    gpio_init(BTN_DOWN);   gpio_set_dir(BTN_DOWN, GPIO_IN);   gpio_pull_up(BTN_DOWN);
    gpio_init(BTN_SELECT); gpio_set_dir(BTN_SELECT, GPIO_IN); gpio_pull_up(BTN_SELECT);
}

int select_payload_menu(ssd1306_t *oled, const char **items, int count) {
    int top = 0;
    bool dirty = true;

    while (true) {
        // === Draw screen ===
        if (dirty) {
            ssd1306_clear(oled);
            for (int i = 0; i < 6; i++) {
                int index = top + i;
                if (index >= count) break;

                char line[22];
                snprintf(line, sizeof(line), "%c %s", (index == selected) ? '>' : ' ', items[index]);
                ssd1306_draw_string(oled, 0, i * 10, 1, line);
            }
            ssd1306_show(oled);
            dirty = false;
        }

        // === Handle input ===
        if (gpio_get(BTN_UP) == 0) {
            if (selected > 0) { selected--; dirty = true; }
            if (selected < top) { top--; dirty = true; }
            sleep_ms(200);
        }

        if (gpio_get(BTN_DOWN) == 0) {
            if (selected < count - 1) { selected++; dirty = true; }
            if (selected >= top + 6) { top++; dirty = true; }
            sleep_ms(200);
        }

        if (gpio_get(BTN_SELECT) == 0) {
            // Wait for release
            while (gpio_get(BTN_SELECT) == 0) {
                tud_task();
                sleep_ms(10);
            }
            return selected;
        }

        tud_task();
        sleep_ms(10);
    }
}
