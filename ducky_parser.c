#include "ducky_parser.h"
#include "pico/stdlib.h"
#include "keymap.h"

//Create a payload, rebuild project and then compile

//-------------------------------------------+
//  Keyword - DELAY
//-------------------------------------------+

static void p_delay(const char *line){
    char *delay_str = line + 6;
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

//-------------------------------------------+
//  Keyword - STRING
//-------------------------------------------+

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

//-------------------------------------------+
//  Keyword - GUI
//-------------------------------------------+  

static void p_gui(const char *line){
    char *key = line + 3;
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

//-------------------------------------------+
//  Keyword - CTRL
//-------------------------------------------+       

static void p_ctrl(const char *line){
    char *key = line + 4;
    while (*key == ' ' || *key == '\t') key++;

    reportQueue *q = get_keyboard_queue();
    int8 keycode = 0;
    
    keycode = keymap[(int8)*key].keycode;

    if (keycode) {
        report_t r = {0};
        r.cmd = CMD_KEY;
        r.data._key.modifier = MOD_LCTRL;
        r.data._key.keycode[0] = keycode;
        enqueue_report(q, &r);
    }
}

//-------------------------------------------+
//  Keyword - SHIFT
//-------------------------------------------+     

static void p_shift(const char *line){
     char *key = line + 5;
    while (*key == ' ' || *key == '\t') key++;

    reportQueue *q = get_keyboard_queue();
    int8 keycode = 0;

    keycode = keymap[(int8)*key].keycode;

    if (keycode) {
        report_t r = {0};
        r.cmd = CMD_KEY;
        r.data._key.modifier = MOD_LSHIFT;
        r.data._key.keycode[0] = keycode;
        enqueue_report(q, &r);
    }
}

//-------------------------------------------+
//  Keyword - ALT
//-------------------------------------------+   

static void p_alt(const char *line){
    char *key = line + 3;
    while (*key == ' ' || *key == '\t') key++;

    reportQueue *q = get_keyboard_queue();
    int8 keycode = 0;

    keycode = keymap[(int8)*key].keycode;
    
    if (keycode) {
        report_t r = {0};
        r.cmd = CMD_KEY;
        r.data._key.modifier = MOD_LALT;
        r.data._key.keycode[0] = keycode;
        enqueue_report(q, &r);
    }
}

//-------------------------------------------+
//  Keyword - CTRL-ALT
//-------------------------------------------+  

static void p_ctrl_alt(const char *line){
    char *key = line + 8;
    while (*key == ' ' || *key == '\t') key++;

    reportQueue *q = get_keyboard_queue();
    int8 keycode = 0;

    keycode = keymap[(int8)*key].keycode;

    if (keycode) {
        report_t r = {0};
        r.cmd = CMD_KEY;
        r.data._key.modifier = MOD_LCTRL | MOD_LALT ;
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
       
        // Handle CTRL-ALT key combination
        else if (strncmp(line, "CTRL-ALT", 8) == 0) {
            p_ctrl_alt(line);
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
    sem_acquire_blocking(&init_comp);       // wait for initialization to complete

    reportQueue *q = get_keyboard_queue();
    parse_duckyscript(payloads[0]);
    parse_duckyscript(payloads[1]);
}

