#include "tusb.h"

#define ITF_NUM_HID 0
#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

const uint8_t desc_hid_report[] = {
    TUD_HID_REPORT_DESC_KEYBOARD()
};

const uint8_t* tud_hid_descriptor_report_cb(uint8_t instance) {
    (void)instance;
    return desc_hid_report;
}

const uint8_t desc_configuration[] = {
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, CONFIG_TOTAL_LEN, 0, 100),
    TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, HID_ITF_PROTOCOL_KEYBOARD, sizeof(desc_hid_report), 0x81, 8, 10)
};

const uint8_t* tud_descriptor_configuration_cb(uint8_t index) {
    (void)index;
    return desc_configuration;
}

const uint8_t desc_device[] = {
    0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 64,
    0xC0, 0x16, 0xDC, 0x05, 0x00, 0x01, 0x01, 0x02,
    0x03, 0x01
};

const uint8_t* tud_descriptor_device_cb(void) {
    return desc_device;
}

const char* string_desc_arr[] = {
    (const char[]) { 0x09, 0x04 },
    "RP2040 Manufacturer",
    "RP2040 HID Keyboard",
    "123456"
};

static uint16_t _desc_str[32];

const uint16_t* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void)langid;
    uint8_t chr_count;

    if (index == 0) {
        _desc_str[1] = 0x0409;
        chr_count = 1;
    } else {
        const char* str = string_desc_arr[index];
        chr_count = strlen(str);
        for (uint8_t i = 0; i < chr_count; i++) {
            _desc_str[1 + i] = str[i];
        }
    }

    _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);
    return _desc_str;
}
