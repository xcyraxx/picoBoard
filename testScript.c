#include "testScript.h"

void testScript(){
    reportQueue *q = get_keyboard_queue();
    
    report_t test[20] = {0};

    // Win + R
    test[0].modifier= MOD_LGUI;
    test[0].keycode[0]=HID_KEY_R; 
    test[0].delay_ms = 100;

    test[1].keycode[0] = HID_KEY_N;
    test[2].keycode[0] = HID_KEY_O;
    test[3].keycode[0] = HID_KEY_T;
    test[4].keycode[0] = HID_KEY_E;
    test[5].keycode[0] = HID_KEY_P;
    test[6].keycode[0] = HID_KEY_A;
    test[7].keycode[0] = HID_KEY_D;

    // Enter
    test[8].keycode[0] = HID_KEY_ENTER;
    test[8].delay_ms = 500;

    // Text Message
    test[9].keycode[0] = HID_KEY_W;
    test[10].keycode[0] = HID_KEY_A;
    test[11].keycode[0] = HID_KEY_S;
    test[12].keycode[0] = HID_KEY_S;
    test[13].keycode[0] = HID_KEY_U;
    test[14].keycode[0] = HID_KEY_P;

    test[15].keycode[0] = HID_KEY_SPACE;

    test[16].keycode[0] = HID_KEY_C;
    test[17].keycode[0] = HID_KEY_U;
    test[18].keycode[0] = HID_KEY_H;
    test[19].keycode[0] = HID_KEY_H;

    for(int i = 0; i < 20; i++){
        enqueue_report(q, &test[i]);
    }

}
