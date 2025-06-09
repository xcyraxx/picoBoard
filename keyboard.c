/*
    This is the keyboard interface for the pico. It is a state machine, having four main states:
    - IDLE
    - KEY_PRESS
    - KEY_RELASE
    - KEY_DELAY

    **A pause state could be implemented if we are going for multithreading all the processes**

    Functions are performed depending on the current state of the machine.
    State of the machine can be changed from outside the interface, although its not advised to do so.

    The report definition for the keyboard is a bit modified from the standard version. 4 bytes for delay have been added.
    This delay byte is not required for the tiny_usb function, it is for the state machine. 
    Do not pass the delay_ms to any tusb functions.

    Since it is using custom delays, pacing is not implemented. Could implement pacing for further optimizations, 
    or if keystrokes are missing.

    Functions are provided for direct sending of keys, bypassing the queue. 
    These functions are defined in keyboard.h, it is advised not to use these functions frequently.

*/


#include "tusb.h"
#include "pico/stdlib.h"
#include "keyboard.h"

static StateType state;

// Initialize everything for keyboard
void keyboard_init(){  
    queue_init();
    set_state_idle(&state);
}

// Definition of get_current_state()
StateType *get_current_state(){
    return &state;
}

// Sends report from queue to system via tud_hid_keyboard_report()
static void send_key(report_t *r){
    if(!tud_hid_ready()) return;
    tud_hid_keyboard_report(0, r->modifier, r->keycode);
}

// Sends release, i.e relase the key after press
static inline void release_key(){
    tud_hid_keyboard_report(0, 0, NULL);
}


// Determines the flow of keyboard tasks
void keyboard_task(){
    static report_t _send;
    static int32 timestamp = 0;
    reportQueue *q = get_keyboard_queue();

    switch(state) {
        case STATE_IDLE:
            if(keyboard_ready()&& !(queue_is_empty(q))){
                dequeue_report(q, &_send);
                send_key(&_send);
                timestamp = time_us_32();
                state = STATE_KEY_PRESS;
            }
            break;
        
        case STATE_KEY_PRESS:
            if((time_us_32() - timestamp) >= 20000) {       // time comparision is done in microseconds
                release_key();
                state = STATE_KEY_RELEASE;
            }
            break;
        
        case STATE_KEY_RELEASE:
            if((time_us_32() - timestamp) >= 20000){
                state = STATE_KEY_DELAY;
                timestamp = time_us_32();                   // reset the timestamp for delay in next state
            }
            break;
        
        case STATE_KEY_DELAY:
            if((time_us_32() - timestamp) >= (_send.delay_ms *1000)){
                state = STATE_IDLE;
            }
            break;
        
        default:
            state = STATE_IDLE;
            break;
    }
    
}

