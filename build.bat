
@echo off
REM ============================================================
REM  build.bat - Build script for RPi 3B+ Bare Metal UART Project
REM
REM  Copyright (c) 2025 VDRDrive
REM  Released under the MIT License
REM  See LICENSE in the project root for full license information.
REM ============================================================

SET OUTPUT_DIR=output

if exist output (
    echo Cleaning output folder...
    rmdir /s /q output
)
IF NOT EXIST %OUTPUT_DIR% mkdir %OUTPUT_DIR%

echo [1] Assembling boot.s...
arm-none-eabi-as boot.s -o %OUTPUT_DIR%\boot.o

echo [2] Compiling main.c...
arm-none-eabi-gcc -c main.c -ffreestanding -O2 -nostdlib -Wall -Wextra -o %OUTPUT_DIR%\main.o

echo [3] Linking kernel.elf...
arm-none-eabi-gcc -nostdlib -T linker.ld %OUTPUT_DIR%\boot.o %OUTPUT_DIR%\main.o -o %OUTPUT_DIR%\kernel.elf

echo [4] Converting to raw binary kernel.img...
arm-none-eabi-objcopy %OUTPUT_DIR%\kernel.elf -O binary --gap-fill=0x00 %OUTPUT_DIR%\kernel.img

echo Build complete! Files are in %OUTPUT_DIR%
pause
