#include "descriptor.h"

tusb_desc_device_t const desc_device = {
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0200,

    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,

    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor = 0xCafe,     // PLACEHOLDER
    .idProduct = 0x4000,     // PLACEHOLDER       
    .bcdDevice =  0x0100,

    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x03,

    .bNumConfigurations  = 1
};

int8 const hid_report_descriptor[] = {
    TUD_HID_REPORT_DESC_KEYBOARD()
};

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

int8 const desc_configuration[] = {
    // CONFIG DESCRIPTOR
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, CONFIG_TOTAL_LEN, 0x00, 100),

    // INTERFACE DESCRIPTOR
    TUD_HID_DESCRIPTOR(0, 0, HID_ITF_PROTOCOL_KEYBOARD, sizeof(hid_report_descriptor), 0x81, 8, 10)
};

/*-----------------STRING DESCRIPTOR------------------------------*/
char const* string_desc_arr[] = {
    (const char[]){0x09, 0x04},         // 0: language (English) 
    "KAAN",                             // 1: Manufacturer
    "DUCKY",                            // 2: Product
    "69420"                             // 3: Serial Number
};
/*----------------------------------------------------------------*/

// DEVICE DESCRIPTOR CALLBACK
int8 const *tud_descriptor_device_cb(void){
    return (int8 const*)&desc_device;
}

// CONFIGURATION DESCRIPTOR CALLBACK
int8 const *tud_descriptor_configuration_cb(int8 index){
    (void)index;
    return desc_configuration;
}

int8 const *tud_hid_descriptor_report_cb(int8 instance){
    (void)instance;
    return hid_report_descriptor;
}

// STRING DESCRIPTOR CALLBACK
int16 const* tud_descriptor_string_cb(int8 index, int16 langid) {
    static int16 _desc_str[32];
    int8 chr_count;

    (void)langid;

    if(!index){
        _desc_str[1] = 0x0409;
        chr_count = 1;
    }
    else{
        if(!(index < sizeof(string_desc_arr)/sizeof(string_desc_arr[0]))) return NULL;

        const char* str = string_desc_arr[index];
        chr_count = 0;

        while(str[chr_count] && chr_count < 31){
            _desc_str[1+chr_count] = str[chr_count];
            chr_count++;
        }
    }

    _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);
    return _desc_str;
}
