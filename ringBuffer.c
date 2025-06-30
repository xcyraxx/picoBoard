/*
    NOTE:
        The way this queue is implemented is by making the queue a global data structure, but it his hidden.
        The only way to access the queue is using a reference to the queue.
        This is done because, no other functions should try and create another instance of the queue.

        Every file that implements ringBuffer will be aware of the queue, but will not know how the queue is defined. 
        Hence giving a layer of abstraction, 

        ** Do not call the queue_init() function in any other file apart from the keyboard
        Calling it can cause the queue to re-initialize, losing all the data previously held in it **

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
    spin_lock_t *lock;
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
    
    int lockID = spin_lock_claim_unused(true);                      // claiming a free lock       
    if(!lockID) return false;
                    
    keyboardQueue.lock = spin_lock_instance(lockID);
    return true;
}

//***************************************************************************************************************//
// These are the thread safe version for the is_empty/full functions. 
// Use these functions for checking the state outside the critical sections

// ** Potential issue **
// If there's constant dequeue/enqueue operations begin performed then these functions may not return
// could face a busy waiting problem, although its unlikely since theres only 2 cores in pico
// If such issues arises then we might have to implement some sort of MCS or ticket-based locks
//***************************************************************************************************************//


bool queue_isEmpty_safe(){                                                // Safe is_empty()
    int32 irq_status = spin_lock_blocking(keyboardQueue.lock);    
    bool result = keyboardQueue.queue_head == -1;
    spin_unlock(keyboardQueue.lock, irq_status);
    return result;
}

bool queue_isFull_safe(){                                               // Safe is_full()
    int32 irq_status = spin_lock_blocking(keyboardQueue.lock);
    bool result = ((keyboardQueue.queue_tail +1 ) % REPORT_QUEUE_SIZE) == keyboardQueue.queue_head;
    spin_unlock(keyboardQueue.lock, irq_status); 
    return result;
}

//***************************************************************************************************************//
//***************************************************************************************************************//


// Check if queue is empty
 static bool queue_is_empty(const reportQueue* q){
    return q->queue_head == -1;
}

// Check if queue is full
static bool queue_is_full(const reportQueue* q){
    return ((q->queue_tail + 1) % REPORT_QUEUE_SIZE) == q->queue_head;
}

// Add to queue
bool enqueue_report(reportQueue *q, const report_t *report ){
   
    while(true) {
        int32 irq_status = spin_lock_blocking(q->lock);                 // ENTER C.S

        if(!(queue_is_full(q))){
            if(q->queue_head == -1)
                q->queue_head = q->queue_tail = 0;
            else
                q->queue_tail= (q->queue_tail + 1) % REPORT_QUEUE_SIZE;

            q->buffer[q->queue_tail] = *report;
            spin_unlock(q->lock, irq_status);
            return true;
        }

        spin_unlock(q->lock, irq_status);                               // EXIT C.S
        tight_loop_contents();
    }
}


// Remove from queue
bool dequeue_report(reportQueue *q, report_t *out){
    bool result = false;

    int32 irq_status = spin_lock_blocking(q->lock);                   // ENTER C.S

    if(queue_is_empty(q))
        result = false;
    
    else{
        *out = q->buffer[q->queue_head];
    
        if(q->queue_head == q->queue_tail){
            q->queue_head = q->queue_tail = -1;                     // reset the queue
        }
        else
            q->queue_head = (q->queue_head + 1) % REPORT_QUEUE_SIZE;
        
        result = true;
    }

    spin_unlock(q->lock, irq_status);                               // EXIT C.S    
    return result;
}
