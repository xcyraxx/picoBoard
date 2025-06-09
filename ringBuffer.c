/*
    NOTE:
        The way this queue is implemented is by making the queue a global data structure, but it his hidden.
        The only way to access the queue is using a reference to the queue.
        This is done because, no other functions should try and create another instance of the queue.

        Every file that implements ringBuffer will be aware of the queue, but will not know how the queue is defined. 
        
        ** Do not call the queue_init() function in any other file apart from the keyboard
        Calling it can cause the queue to re-initialize, potentially losing all the data previously held in it **

    How to use:
        1. When trying to use the queue, first get the instance of the keyboard queue using get_keyboard_queue,
           It returns a pointer to the keyboard queue
        
        2. While enqueueing, pass the pointer to the queue along with the report to be enqueued. Same with dequeueing
       
    
*/


#include "ringBuffer.h"

struct _reportQueue{                          // Queue definiton
    report_t buffer[REPORT_QUEUE_SIZE];      
    sint32 queue_head;
    sint32 queue_tail;
};

// The actual queue
static reportQueue keyboardQueue;             // Queue instance


// Get pointer for the report queue
reportQueue *get_keyboard_queue(){
    return &keyboardQueue;
}

// Initialize the queue
bool queue_init(){
    keyboardQueue.queue_head= -1;
    keyboardQueue.queue_tail= -1;
    memset(keyboardQueue.buffer, 0, sizeof(keyboardQueue.buffer));   // set every value tp 0x00
    return true;
}

// Check if queue is empty
bool queue_is_empty(const reportQueue* q){
    return q->queue_head == -1;
}

// Check if queue is full
bool queue_is_full(const reportQueue* q){
    return (q->queue_head == 0 && q->queue_tail == REPORT_QUEUE_SIZE-1) || 
           ((q->queue_tail + 1) == q->queue_head);
}

// Add to queue
bool enqueue_report(const report_t *report, reportQueue *q){
    if(queue_is_full(q)) return false;

    if(q->queue_head == -1)
        q->queue_head = 0;

    q->queue_tail= (q->queue_tail + 1) % REPORT_QUEUE_SIZE;
    q->buffer[q->queue_tail] = *report;
   
    return true;
}


// Remove from queue
bool dequeue_report(report_t *out, reportQueue *q){
    if(queue_is_empty(q)) return false;

    *out = q->buffer[q->queue_head];
   
    if(q->queue_head == q->queue_tail){
        q->queue_head = q->queue_tail = -1;
    }
    else{
        q->queue_head = (q->queue_head + 1) % REPORT_QUEUE_SIZE;
    }
    
    return true;
}
