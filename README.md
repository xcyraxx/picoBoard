  # picoBoard 🦆📟

picoBoard is a **USB Rubber Ducky–style device** built on the [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/).  
It allows you to execute keystroke injection attacks with a **dynamic payload system** and an **OLED display** to select payloads directly on the device.

---

## ✨ Features
- **Dynamic Payload System** – Load multiple payloads and select at runtime.
- **OLED Display Support** – Browse and choose payloads easily via SSD1306 screen.
- **DuckyScript Parsing** – Compatible with standard Rubber Ducky–style scripts.
- **USB HID Emulation** – Acts as a keyboard to inject keystrokes into target machines.
- **Raspberry Pi Pico Support** – Lightweight, inexpensive, and flexible hardware base.

---

## 📂 Project Structure
```bash
picoBoard/
├── .gitignore
├── include/                  # Header files
├── payloads/                 # DuckyScript payloads
├── CMakeLists.txt            # Main CMake build config
├── ducky_parser.c            # DuckyScript parsing logic
├── generate_payloads.cmake   # Payload build script
├── keyboard.c                # USB keyboard emulation
├── main.c                    # Firmware entry point
├── pico_sdk_import.cmake     # Pico SDK integration
├── ringBuffer.c              # Buffer management
├── ssd1306.c                 # OLED display driver
├── ui.c                      # User interface and menu logic
├── usb_descriptor.c          # USB HID descriptors

```
---

## ⚡ Getting Started

### 🔧 Requirements
- Raspberry Pi Pico (RP2040-based board)
- OLED Display (SSD1306, I²C)
- CMake + Pico SDK installed
- USB cable for flashing

### 🛠️ Build Instructions
1. Clone this repository:
   ```bash
     git clone https://github.com/yourusername/picoBoard.git
     cd picoBoard
  Initialize Pico SDK submodules (if required):
    ```
      git submodule update --init
    ```
    
2. Create a build directory and compile:
    ```
      mkdir build && cd build
      cmake ..
      make
    ```
3. Flash the UF2 file to your Pico:

   - Hold the BOOTSEL button while connecting your Pico to USB.
   - Copy the generated .uf2 file from build/ to the Pico’s storage.

### 📜 Payloads

   - Place DuckyScript payloads inside the payloads/ folder.
   - Payloads are compiled during the build process using generate_payloads.cmake.
   - Use the OLED interface to scroll through and select payloads on the fly.

### 🖼️ Display UI

The SSD1306 OLED is used to:

  - Show the current payload list.
  - Display execution status.
  - Provide simple navigation for payload selection.

### 🚧 Roadmap / TODO

- Add custom payload editor over USB storage.
- Improve DuckyScript compatibility.
- Add configuration menu on device.
- Support multiple display types.
---
## ⚠️ Disclaimer

This project is for educational and research purposes only.
Do not use picoBoard for malicious purposes. The authors are not responsible for misuse.
