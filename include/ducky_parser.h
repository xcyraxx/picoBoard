#ifndef DUCKY_PARSER_H
#define DUCKY_PARSER_H

#include <stdlib.h>
#include <string.h>
#include "ringBuffer.h"
#include "class/hid/hid.h"
#include "payloads.h"
#include "shd_sync.h"


void testScript();
void parse_duckyscript(const char *script);
void entry(void);

#endif
