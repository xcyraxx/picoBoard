#ifndef _TUSB_CONFIG_H
#define _TUSB_CONFIG_H

#define CFG_TUSB_MCU OPT_MCU_RP2040
#define CFG_TUSB_RHPORT0_MODE OPT_MODE_DEVICE
#define CFG_TUSB_OS OPT_OS_PICO

#define CFG_TUD_ENDPOINT0_SIZE 64

#define CFG_TUD_HID 1
#define CFG_TUD_CDC 0
#define CFG_TUD_MSC 0
#define CFG_TUD_MIDI 0
#define CFG_TUD_VENDOR 0


#endif
