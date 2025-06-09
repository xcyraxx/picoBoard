#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include<stdbool.h>
#include<stdint.h>
#include<string.h>

typedef uint8_t int8;
typedef uint16_t int16;
typedef uint32_t int32;
typedef int32_t sint32;

#define MAX_COUNT 6
#define REPORT_QUEUE_SIZE 128


typedef struct{
    int8 modifier;
    int8 reserved;
    int8 keycode[MAX_COUNT];
    int32 delay_ms;
} report_t;

typedef struct _reportQueue reportQueue;

reportQueue *get_keyboard_queue(void);

bool queue_init();
bool queue_is_empty(const reportQueue* q);
bool queue_is_full(const reportQueue* q);
bool enqueue_report(reportQueue *q, const report_t *report );
bool dequeue_report(reportQueue *q, report_t *out);


#endif