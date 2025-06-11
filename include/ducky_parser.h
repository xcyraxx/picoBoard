#ifndef DUCKY_PARSER_H
#define DUCKY_PARSER_H

#include <stdlib.h>
#include <string.h>
#include "ringBuffer.h"
#include "class/hid/hid.h"
#include "payloads.h"
#include "shd_sync.h"


#define MOD_LGUI 0x08
#define MOD_LCTRL 0x01
#define MOD_LSHIFT 0x02
#define MOD_LALT 0x04
#define HID_KEY_LEFT_BRACKET 0x1A
#define HID_KEY_RIGHT_BRACKET 0x1B
#define HID_KEY_DOT 0x37
#define HID_KEY_EXCLAMATION 0x1E
#define HID_KEY_ESC 0x29


void testScript(void);
void parse_duckyscript(const char *script);

#endif
