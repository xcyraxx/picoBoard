#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include<stdbool.h>
#include<stdint.h>
#include<string.h>
#include "pico/stdlib.h"
#include "hardware/sync.h"

typedef uint8_t int8;
typedef uint16_t int16;
typedef uint32_t int32;
typedef int32_t sint32;

#define MAX_COUNT 6
#define MAX_STRING_LEN 64
#define REPORT_QUEUE_SIZE 1024

typedef enum{                                // For identifying the type of command
    CMD_KEY,
    CMD_DELAY,
}commandType;

typedef struct{
    commandType cmd;
    union{                                   // struct within union for future expansion
        struct{                              // If we are adding more types, then define them inside the union
            int8 modifier;
            int8 reserved;
            int8 keycode[MAX_COUNT];
        } _key;
    } data; 
    int32 delay_ms;
} report_t;

typedef struct _reportQueue reportQueue;

reportQueue *get_keyboard_queue(void);

bool queue_init();
static bool queue_is_empty(const reportQueue* q);
static bool queue_is_full(const reportQueue* q);
bool enqueue_report(reportQueue *q, const report_t *report );
bool dequeue_report(reportQueue *q, report_t *out);


#endif
