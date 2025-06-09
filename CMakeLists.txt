# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(pico_hid_keyboard C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()
include_directories(${PICO_SDK_PATH}/lib/tinyusb/src)
include_directories(${PICO_SDK_PATH}/lib/tinyusb/src/class/hid)
add_executable(
    pico_hid_keyboard
    main.c
    descriptors.c
    keyboard.c
    ringBuffer.c
    testScript.c
)


target_include_directories(pico_hid_keyboard PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

pico_enable_stdio_usb(hid_keyboard 0)  # 0 = Enable USB
pico_enable_stdio_uart(hid_keyboard 0) # 0 = Disable UART (optional)

target_link_libraries(pico_hid_keyboard
    pico_stdlib
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(pico_hid_keyboard)
