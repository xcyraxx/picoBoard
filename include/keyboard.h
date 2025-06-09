#ifndef KEYBOARD_H
#define KEYBOARD_H


#include<stdint.h>
#include<stdbool.h>
#include "ringBuffer.h"

typedef uint8_t int8;
typedef uint16_t int16;
typedef uint32_t int32;

// State definition
typedef enum{
    STATE_IDLE,
    STATE_KEY_PRESS, 
    STATE_KEY_RELEASE, 
    STATE_KEY_DELAY
} StateType;


void keyboard_init(void);
void keyboard_task(void);

static inline bool keyboard_ready(void);
static inline void send_report(report_t *r);
static inline void send_release();


// Returns the current state of the system
StateType *get_current_state();

// check if keyboard is ready to send
static inline bool keyboard_ready(){
    return tud_hid_ready();
}

// This function is for direct sending of reports. Reports dont have to be added to queue.
// Do not call it in main 
static inline void send_report(report_t *r){                              
    tud_hid_keyboard_report(0, r->modifier, r->keycode);       
}    

// To be called only after send_report() 
static inline void send_release(){
    tud_hid_keyboard_report(0, 0, NULL);
}


// To set the initial state for the state machine
static inline void set_state_idle(StateType *s){
    *s = STATE_IDLE;
}

// Set state to idle
static inline void set_state_key_press(StateType *s){
    *s = STATE_KEY_PRESS;
}

// Set state to key release
static inline void set_state_key_release(StateType *s){
    *s = STATE_KEY_RELEASE;
}

// Set state to key delay
static inline void set_state_key_delay(StateType *s){
    *s = STATE_KEY_DELAY;
}

#endif
