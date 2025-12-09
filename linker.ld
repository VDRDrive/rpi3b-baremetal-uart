/*
 * Copyright (c) 2025 VDRDrive
 *
 * This software is released under the MIT License.
 * See LICENSE file in the project root for full license information.
 */


ENTRY(_start)

SECTIONS
{
    . = 0x8000;

    .text : { *(.text*) }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss : { *(.bss*) }
}
