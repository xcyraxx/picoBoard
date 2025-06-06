#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include<stdint.h>
#include "tusb.h"

typedef uint8_t int8;
typedef uint16_t int16;

// For HID descriptor
int8 const *tud_hid_descriptor_report_cb(int8 instance);

// Descriptor callback
int8 const *tud_descriptor_device_cb(void);

// Descriptor callback config
int8 const *tud_descriptor_configuration_cb(int8 index);


#endif
