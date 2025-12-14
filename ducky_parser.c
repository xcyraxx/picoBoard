#include "ducky_parser.h"
#include "pico/stdlib.h"
#include "keymap.h"
#include "ui.h" 
#include "ringBuffer.h"
#include "tusb.h"
#include "keyboard.h"


//Create a payload, rebuild project and then compile

//------------------------------------------------------------------+
//                       Keyword - DELAY
//------------------------------------------------------------------+

static void p_delay(const char *line){
    const char *delay_str = line + 6;
    while (*delay_str == ' ' || *delay_str == '\t') delay_str++;
    int ms = atoi(delay_str);
    if (ms > 0) {
        reportQueue *q = get_keyboard_queue();
        report_t r = {0};
        r.cmd = CMD_DELAY;
        r.delay_ms = ms;
        enqueue_report(q, &r);
    }
}

//------------------------------------------------------------------+
//                       Keyword - STRING
//------------------------------------------------------------------+

static void p_string(const char *line){
    const char *str = line + 7;
    reportQueue *q = get_keyboard_queue();
    int8 keycode = 0;
    int8 modifier = 0;
    
    while (*str) {
        keycode = keymap[(int8)*str].keycode;
        modifier = keymap[(int8)*str].modifier;

        if(keycode){
            report_t r = {0};
            r.cmd = CMD_KEY;
            r.data._key.keycode[0] = keycode;
            r.data._key.modifier = modifier;
            enqueue_report(q, &r);
        }
        str++;
    }
}

//------------------------------------------------------------------+
//                       Keyword - GUI
//------------------------------------------------------------------+

static void p_gui(const char *line){
    const char *key = line + 3;
    while (*key == ' ' || *key == '\t') key++;
    //check which letter comes after GUI in one line and press
    reportQueue *q = get_keyboard_queue();
    int8 keycode = 0;

    keycode = keymap[(int8)*key].keycode;

    if (keycode) {
        report_t r = {0};
        r.cmd = CMD_KEY;
        r.data._key.modifier = MOD_LGUI;
        r.data._key.keycode[0] = keycode;
        enqueue_report(q, &r);
    }
}

//------------------------------------------------------------------+
//                        Keyword - CTRL
//------------------------------------------------------------------+

static void p_ctrl(const char *line){
    const char *key = line + 4;
    while (*key == ' ' || *key == '\t') key++;
    int8 keycode = 0, i=0, modifier = MOD_LCTRL;

 //------------- Tokenize the line ------------------  
    char *saveptr;
    char *tokens[5] = {0};
    char *word = strdup(key);

    char *token = strtok_r(word, " ", &saveptr);

    while(token != NULL && i < 5){
        tokens[i++] = token;
        token = strtok_r(NULL, " ", &saveptr);
    }
 //--------------------------------------------------

    for(int a = 0; tokens[a] != 0; a++){
     // HANDLE SHIFT
        if(strcmp(tokens[a], "SHIFT") == 0)
            modifier |= MOD_LSHIFT;
     // HANDLE ALT
        else if(strcmp(tokens[a], "ALT") == 0)
            modifier |= MOD_LALT;
     // HANDLE GUI
        else if(strcmp(tokens[a], "GUI") == 0)
            modifier |= MOD_LGUI;
     // HANDLE F1-12
        else if(tokens[a][0] == 'F'){                                      
            int32 index = atoi(tokens[a]+1);   

            if(index >= 1 && index <= 12){
                keycode = f_keys[index];
                break;
            }
        }
     // HANDLE OTHER KEYS 
        for(int j = 0; j < (sizeof(keyEntry)/sizeof(keyEntry[0])); j++){
            if(strcmp(tokens[a], keyEntry[j].keyname) == 0){
                keycode = keyEntry[j].keycode; 
                break;
            }
        }
    }
    
    reportQueue *q = get_keyboard_queue();

    if (!keycode){
        if(i == 1 && strlen(key) == 1)
            keycode = keymap[(int8)*key].keycode;
       
        else if(i>1 && strlen(tokens[i-1]) == 1)      // Assuming that the last token is always a single character
            keycode = keymap[(int8)tokens[i-1][0]].keycode;    
    }
    
    report_t r = {0};
    r.cmd = CMD_KEY;
    r.data._key.modifier = modifier;
    r.data._key.keycode[0] = keycode;
    enqueue_report(q, &r);
    free(word);
}

//------------------------------------------------------------------+
//                       Keyword - SHIFT
//------------------------------------------------------------------+

static void p_shift(const char *line){
    const char *key = line + 5;
    while (*key == ' ' || *key == '\t') key++;
    int8 keycode = 0, i=0, modifier = MOD_LSHIFT;

 //------------- Tokenize the line ------------------  
    char *saveptr;
    char *tokens[5] = {0};
    char *word = strdup(key);

    char *token = strtok_r(word, " ", &saveptr);

    while(token != NULL && i < 5){
        tokens[i++] = token;
        token = strtok_r(NULL, " ", &saveptr);
    }
 //--------------------------------------------------

    for(int a = 0; tokens[a] != 0; a++){
     // HANDLE ALT
        if(strcmp(tokens[a], "ALT") == 0)
            modifier |= MOD_LALT;
     // HANDLE GUI
        else if(strcmp(tokens[a], "GUI") == 0)
            modifier |= MOD_LGUI;
     // HANDLE F1-12
        else if(tokens[a][0] == 'F'){                                      
            int32 index = atoi(tokens[a]+1);   

            if(index >= 1 && index <= 12){
                keycode = f_keys[index];
                break;
            }
        }
     // HANDLE OTHER KEYS
        for(int j = 0; j < (sizeof(keyEntry)/sizeof(keyEntry[0])); j++){
            if(strcmp(tokens[a], keyEntry[j].keyname) == 0){
                keycode = keyEntry[j].keycode; 
                break;
            }
        }
    }

    reportQueue *q = get_keyboard_queue();

    if (!keycode){
        if(i == 1 && strlen(key) == 1)
            keycode = keymap[(int8)*key].keycode;
       
        else if(i>1 && strlen(tokens[i-1]) == 1)      // Assuming that the last token is always a single character
            keycode = keymap[(int8)tokens[i-1][0]].keycode;     
    }
    
    report_t r = {0};
    r.cmd = CMD_KEY;
    r.data._key.modifier = modifier;
    r.data._key.keycode[0] = keycode;
    enqueue_report(q, &r);
    free(word);

}

//------------------------------------------------------------------+
//                         Keyword - ALT
//------------------------------------------------------------------+   

static void p_alt(const char *line){
    const char *key = line + 3;
    while (*key == ' ' || *key == '\t') key++;
    int8 keycode = 0, i=0, modifier = MOD_LALT;

 //------------- Tokenize the line ------------------  
    char *saveptr;
    char *tokens[3] = {0};
    char *word = strdup(key);

    char *token = strtok_r(word, " ", &saveptr);

    while(token != NULL && i < 5){
        tokens[i++] = token;
        token = strtok_r(NULL, " ", &saveptr);
    }
 //--------------------------------------------------

for(int a = 0; tokens[a] != 0; a++){
    // HANDLE GUI
        if(strcmp(tokens[a], "GUI") == 0)
            modifier |= MOD_LGUI;    
    // HANDLE F1-12
        else if(tokens[a][0] == 'F'){                                      
            int32 index = atoi(tokens[a]+1);   

            if(index >= 1 && index <= 12){
                keycode = f_keys[index];
                break;
            }
        }
    
    // HANDLE OTHER KEYS
        for(int j = 0; j < (sizeof(keyEntry)/sizeof(keyEntry[0])); j++){
            if(strcmp(tokens[a], keyEntry[j].keyname) == 0){
                keycode = keyEntry[j].keycode; 
                break;
            }
        }
    }

    reportQueue *q = get_keyboard_queue();

    if (!keycode){
        if(i == 1 && strlen(key) == 1)
            keycode = keymap[(int8)*key].keycode;
       
        else if(i>1 && strlen(tokens[i-1]) == 1)      // Assuming that the last token is always a single character
            keycode = keymap[(int8)tokens[i-1][0]].keycode;  
    }
    
    report_t r = {0};
    r.cmd = CMD_KEY;
    r.data._key.modifier = modifier;
    r.data._key.keycode[0] = keycode;
    enqueue_report(q, &r);
    free(word);
}


//------------------------------------------------------------------+
//                       Keyword - F1-12
//------------------------------------------------------------------+

static void p_func(const char *line){
   
    const char *key = line;
    while(*key ==  ' ' || *key == '\t' || *key== 'F') key++;

    int32 index = atoi(key);

    reportQueue *q = get_keyboard_queue();
    int8 keycode = 0;

    if(keycode = f_keys[index]) {
        report_t r = {0};
        r.cmd = CMD_KEY;
        r.data._key.keycode[0] = keycode;
        
        enqueue_report(q, &r);
    }
}


void parse_duckyscript(const char *script) {
    if (script == NULL) return;

    char *script_copy = strdup(script);                 // Copy the script
    if (!script_copy) return;               

    char *saveptr;
    char *line = strtok_r(script_copy, "\n", &saveptr);


    while (line != NULL) {
        // Skip leading whitespace
        while (*line == ' ' || *line == '\t') line++;

        // Ignore empty lines
        if (*line == '\0') {
            line = strtok_r(NULL, "\n", &saveptr);
            continue;
        }

        // Handle REM (comment)
        if (strncmp(line, "REM", 3) == 0) {
            // Do nothing for comments
        }

        // Handle delay
        else if (strncmp(line, "DELAY ", 6) == 0) { 
            p_delay(line);
        }

        // Handle string
        else if (strncmp(line, "STRING ", 7) == 0) {
           p_string(line);
        } 

        // Handle gui
        else if (strncmp(line, "GUI", 3) == 0) {
           p_gui(line);
        }
 
        //-------------------------------------------
        //  Keyword - ENTER
        //-------------------------------------------         
        else if (strncmp(line, "ENTER", 5) == 0) {
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_ENTER}});
        } 

        //-------------------------------------------
        //  Keyword - ESC
        //-------------------------------------------         
        else if (strncmp(line, "ESC", 3) == 0) {
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_ESCAPE}});
        } 
        
        //-------------------------------------------
        //  Keyword - BACKSPACE
        //-------------------------------------------         
        else if (strncmp(line, "BACKSPACE", 9) == 0) {
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_BACKSPACE}});
        } 

        //-------------------------------------------
        //  Keyword - TAB
        //-------------------------------------------         
        else if (strncmp(line, "TAB", 3) == 0) {
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_TAB}});
        }
        
        // Handle ctrl
        else if (strncmp(line, "CTRL", 4) == 0) {
            p_ctrl(line);
        }
        
        // Handle shift
        else if (strncmp(line, "SHIFT", 5) == 0) {
            p_shift(line);
        }     

        // Handle alt
        else if (strncmp(line, "ALT", 3) == 0) {
           p_alt(line);
        }
       
        //-------------------------------------------------------------------------------------------------------
        //                                            ARROW KEYS
        //-------------------------------------------------------------------------------------------------------   

        else if (strncmp(line, "LEFT_ARROW", 10) == 0) {
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_ARROW_LEFT}});
        }

        else if (strncmp(line, "RIGHT_ARROW", 11) == 0) {
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_ARROW_RIGHT}});
        }

        else if (strncmp(line, "UP_ARROW", 8) == 0){
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_ARROW_UP}});
        }
        
        else if (strncmp(line, "DOWN_ARROW", 10) == 0){
            reportQueue *q = get_keyboard_queue();
            enqueue_report(q, &(report_t){.cmd=CMD_KEY, .data._key.keycode = {HID_KEY_ARROW_DOWN}});
        }
        

        //-------------------------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------------------------

        // Handle F1-12
        else if (*line == 'F'){
            p_func(line);
        }
          
        else {
            // placeholder for unrecognized commands
        }
        // Next line
        line = strtok_r(NULL, "\n", &saveptr);
    }
    free(script_copy);
}

void testScript(){

    reportQueue *q = get_keyboard_queue();
    parse_duckyscript(payloads[selected]);
}

void entry(){
    sem_acquire_blocking(&init_comp);       // wait for initialization to complete
    testScript();

    // wait for queue to empty and keyboard to be idle
    while(!queue_isEmpty_safe() || *get_current_state() != STATE_IDLE){
        sleep_ms(10);
    }

    // blink LED twice
    #ifdef PICO_DEFAULT_LED_PIN
    for(int i=0; i<2; i++){
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(200);
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(200);
    }
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    #endif

    ssd1306_clear(&oled);
    ssd1306_draw_string(&oled, 0, 0, 1, "Completed");
    ssd1306_show(&oled);
}

