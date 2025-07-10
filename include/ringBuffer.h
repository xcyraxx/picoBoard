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

#define MAX_COUNT 6              // MAX no. of keys
#define REPORT_QUEUE_SIZE 1024   // MAX Size of Queue

typedef enum{
    CMD_KEY,
    CMD_DELAY,
}commandType;

typedef struct{
    commandType cmd;
    union{
        struct{										// struct within union for future expansion
            int8 modifier;							// If we are adding more types, then define them inside the union
            int8 reserved;
            int8 keycode[MAX_COUNT];
        } _key;
    } data; 
    int32 delay_ms;
} report_t;

typedef struct _reportQueue reportQueue;

reportQueue *get_keyboard_queue(void);

bool queue_init();
bool enqueue_report(reportQueue *q, const report_t *report );
bool dequeue_report(reportQueue *q, report_t *out);

bool queue_isEmpty_safe(void);
bool queue_isFull_safe(void); 



#endif
