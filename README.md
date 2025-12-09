# Raspberry Pi 3B+ Bare-Metal UART “Hello World”

This project demonstrates a minimal bare-metal program running on the Raspberry Pi 3B+, printing text continuously over UART0.  
No Linux or OS is used — just ARMv8 assembly + C.

---

## Features

- Bare-metal boot (no OS)
- GPIO14/15 configured for UART0
- UART initialized at 115200 baud
- Simple “Hello World” output loop
- ARM assembly startup + C main()
- Build using arm-none-eabi-gcc

---

# UART Pin Connections (RPi 3B+)

UART0 pins:

GPIO14  → Pin 8  → TXD0  
GPIO15  → Pin 10 → RXD0  
GND     → Pin 6  → Ground

Connect USB-TTL adapter:

USB-TTL RX → Pin 8 (TXD0)  
USB-TTL TX → Pin 10 (RXD0)  
USB-TTL GND → Pin 6 (GND)

IMPORTANT: Do NOT connect 5V from USB-TTL to the Pi. UART is 3.3V only.

Serial terminal settings:

Baud: 115200  
Data bits: 8  
Stop: 1  
Parity: None  
Flow control: None

---

# Build Instructions (Windows)

1. Download and install the ARM GCC Toolchain:

Arm GNU Toolchain (arm-none-eabi) for Windows (mingw-w64)

Example file:
arm-gnu-toolchain-14.3.rel1-mingw-w64-i686-arm-none-eabi.zip

2. Add the toolchain’s bin/ folder to your PATH.

3. Verify installation:
arm-none-eabi-gcc --version

---

# Build the Project

This repo includes build.bat which:

- Cleans the output/ folder
- Assembles boot.s
- Compiles main.c
- Links using linker.ld
- Produces kernel.img

Run:
build.bat

Output goes to:
output/kernel.img

---

# SD Card Setup

Use a fresh SD card formatted FAT32.

Copy these files to the SD card root:

bootcode.bin  
start.elf  
fixup.dat  
config.txt  
kernel.img

Minimal config.txt:

enable_uart=1  
kernel=kernel.img  
arm_64bit=0
core_freq=250


(Forces firmware to load kernel.img at address 0x8000)

---

# Running the Program

1. Insert SD card into Raspberry Pi 3B+  
2. Connect USB-TTL adapter  
3. Open serial terminal @ 115200  
4. Power the Pi

Expected output:

HELLO WORLD FROM RPI 3B+ BARE METAL!  
HELLO WORLD FROM RPI 3B+ BARE METAL!  
...

---

# Boot Flow Explained

1. GPU loads bootcode.bin  
2. GPU loads start.elf  
3. GPU reads config.txt  
4. GPU loads kernel.img to physical address 0x8000  
5. Execution jumps to _start in boot.s  
6. boot.s sets stack and calls main()  
7. main() initializes UART and prints text

---

# Project Structure

boot.s  
main.c  
linker.ld  
build.bat  
README.md

---

