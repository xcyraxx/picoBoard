#pragma once
#include "ssd1306.h"

#define BTN_UP     26
#define BTN_DOWN   19
#define BTN_SELECT 8

extern int selected;
void init_buttons();
int select_payload_menu(ssd1306_t *oled, const char **items, int count);
extern ssd1306_t oled;

