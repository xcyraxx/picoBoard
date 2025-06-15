#ifndef KEYMAP_H
#define KEYMAP_H 

#include "class/hid/hid.h"

#define MOD_LSHIFT 0x02
#define MOD_LGUI 0x08
#define MOD_LCTRL 0x01
#define MOD_LALT 0x04


typedef struct {
    uint8_t keycode;
    uint8_t modifier;
} keymap_t; 

static const keymap_t keymap[128]  = {
    [' ']  = {HID_KEY_SPACE, 0}, 
    ['!']  = {HID_KEY_1,  MOD_LSHIFT},
    ['"']  = {HID_KEY_APOSTROPHE, MOD_LSHIFT},
    ['#']  = {HID_KEY_3, MOD_LSHIFT},
    ['$']  = {HID_KEY_4, MOD_LSHIFT}, 
    ['%']  = {HID_KEY_5, MOD_LSHIFT},
    ['&']  = {HID_KEY_7, MOD_LSHIFT},
    ['\''] = {HID_KEY_APOSTROPHE, 0},
    ['(']  = {HID_KEY_9, MOD_LSHIFT},
    [')']  = {HID_KEY_0, MOD_LSHIFT},
    ['*']  = {HID_KEY_8, MOD_LSHIFT},
    ['+']  = {HID_KEY_EQUAL, MOD_LSHIFT},
    [',']  = {HID_KEY_COMMA, 0},
    ['-']  = {HID_KEY_MINUS, 0},
    ['.']  = {HID_KEY_PERIOD, 0},
    ['/']  = {HID_KEY_SLASH, 0},

    ['0']  = {HID_KEY_0, 0},
    ['1']  = {HID_KEY_1, 0},
    ['2']  = {HID_KEY_2, 0},
    ['3']  = {HID_KEY_3, 0},
    ['4']  = {HID_KEY_4, 0},
    ['5']  = {HID_KEY_5, 0},
    ['6']  = {HID_KEY_6, 0},
    ['7']  = {HID_KEY_7, 0},
    ['8']  = {HID_KEY_8, 0},
    ['9']  = {HID_KEY_9, 0},

    [':']  = {HID_KEY_SEMICOLON, MOD_LSHIFT},
    [';']  = {HID_KEY_SEMICOLON, 0},
    ['<']  = {HID_KEY_COMMA, MOD_LSHIFT},
    ['=']  = {HID_KEY_EQUAL, 0},
    ['>']  = {HID_KEY_PERIOD, MOD_LSHIFT},
    ['?']  = {HID_KEY_SLASH, MOD_LSHIFT},
    ['@']  = {HID_KEY_2, MOD_LSHIFT},

    ['A']  = {HID_KEY_A, MOD_LSHIFT},
    ['B']  = {HID_KEY_B, MOD_LSHIFT},
    ['C']  = {HID_KEY_C, MOD_LSHIFT},
    ['D']  = {HID_KEY_D, MOD_LSHIFT},
    ['E']  = {HID_KEY_E, MOD_LSHIFT},
    ['F']  = {HID_KEY_F, MOD_LSHIFT},
    ['G']  = {HID_KEY_G, MOD_LSHIFT},
    ['H']  = {HID_KEY_H, MOD_LSHIFT},
    ['I']  = {HID_KEY_I, MOD_LSHIFT},
    ['J']  = {HID_KEY_J, MOD_LSHIFT},
    ['K']  = {HID_KEY_K, MOD_LSHIFT},
    ['L']  = {HID_KEY_L, MOD_LSHIFT},
    ['M']  = {HID_KEY_M, MOD_LSHIFT},
    ['N']  = {HID_KEY_N, MOD_LSHIFT},
    ['O']  = {HID_KEY_O, MOD_LSHIFT},
    ['P']  = {HID_KEY_P, MOD_LSHIFT},
    ['Q']  = {HID_KEY_Q, MOD_LSHIFT},
    ['R']  = {HID_KEY_R, MOD_LSHIFT},
    ['S']  = {HID_KEY_S, MOD_LSHIFT},
    ['T']  = {HID_KEY_T, MOD_LSHIFT},
    ['U']  = {HID_KEY_U, MOD_LSHIFT},
    ['V']  = {HID_KEY_V, MOD_LSHIFT},
    ['W']  = {HID_KEY_W, MOD_LSHIFT},
    ['X']  = {HID_KEY_X, MOD_LSHIFT},
    ['Y']  = {HID_KEY_Y, MOD_LSHIFT},
    ['Z']  = {HID_KEY_Z, MOD_LSHIFT},

    ['[']  = {HID_KEY_BRACKET_LEFT, 0},
    ['\\'] = {HID_KEY_BACKSLASH, 0},
    [']']  = {HID_KEY_BRACKET_RIGHT, 0},
    ['^']  = {HID_KEY_6, MOD_LSHIFT},
    ['_']  = {HID_KEY_MINUS, MOD_LSHIFT},
    ['`']  = {HID_KEY_GRAVE, 0},

    ['a']  = {HID_KEY_A, 0},
    ['b']  = {HID_KEY_B, 0},
    ['c']  = {HID_KEY_C, 0},
    ['d']  = {HID_KEY_D, 0},
    ['e']  = {HID_KEY_E, 0},
    ['f']  = {HID_KEY_F, 0},
    ['g']  = {HID_KEY_G, 0},
    ['h']  = {HID_KEY_H, 0},
    ['i']  = {HID_KEY_I, 0},
    ['j']  = {HID_KEY_J, 0},
    ['k']  = {HID_KEY_K, 0},
    ['l']  = {HID_KEY_L, 0},
    ['m']  = {HID_KEY_M, 0},
    ['n']  = {HID_KEY_N, 0},
    ['o']  = {HID_KEY_O, 0},
    ['p']  = {HID_KEY_P, 0},
    ['q']  = {HID_KEY_Q, 0},
    ['r']  = {HID_KEY_R, 0},
    ['s']  = {HID_KEY_S, 0},
    ['t']  = {HID_KEY_T, 0},
    ['u']  = {HID_KEY_U, 0},
    ['v']  = {HID_KEY_V, 0},
    ['w']  = {HID_KEY_W, 0},
    ['x']  = {HID_KEY_X, 0},
    ['y']  = {HID_KEY_Y, 0},
    ['z']  = {HID_KEY_Z, 0},
    
    ['{']  = {HID_KEY_BRACKET_LEFT, MOD_LSHIFT},
    ['|']  = {HID_KEY_BACKSLASH, MOD_LSHIFT},
    ['}']  = {HID_KEY_BRACKET_RIGHT, MOD_LSHIFT},
    ['~']  = {HID_KEY_GRAVE, MOD_LSHIFT},

    ['\n'] = {HID_KEY_ENTER, 0},
    ['\t'] = {HID_KEY_TAB, 0},
};

#endif