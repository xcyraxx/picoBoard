#include "testScript.h"

void testScript(){
    reportQueue *q = get_keyboard_queue();
    
    report_t test[13] = {0};

    // Win + R
    test[0].modifier= MOD_LGUI;
    test[0].keycode[0]=HID_KEY_R; 
    test[0].delay_ms = 100;

    // Enter
    test[1].keycode[0] = HID_KEY_ENTER;
    test[1].delay_ms = 500;

    // Text Message
    test[2].keycode[0] = HID_KEY_W;
    test[3].keycode[0] = HID_KEY_A;
    test[4].keycode[0] = HID_KEY_S;
    test[5].keycode[0] = HID_KEY_S;
    test[6].keycode[0] = HID_KEY_U;
    test[7].keycode[0] = HID_KEY_P;

    test[8].keycode[0] = HID_KEY_SPACE;

    test[9].keycode[0] = HID_KEY_C;
    test[10].keycode[0] = HID_KEY_U;
    test[11].keycode[0] = HID_KEY_H;
    test[12].keycode[0] = HID_KEY_H;

    for(int i = 0; i < 13; i++){
        enqueue_report(&test[i], q);
    }

}