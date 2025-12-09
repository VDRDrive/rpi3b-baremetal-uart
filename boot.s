
/*
 * Copyright (c) 2025 VDRDrive
 *
 * This software is released under the MIT License.
 * See LICENSE file in the project root for full license information.
 */

/* boot.s - Raspberry Pi 3B+ bare-metal startup (32-bit) */

.global _start
.extern main

.section .text
_start:
    /* Only run on core 0 */
    mrc p15, 0, r0, c0, c0, 5
    and r0, r0, #0x3
    cmp r0, #0
    bne hang

    /* Set stack pointer */
    ldr sp, =0x8000

    /* Jump to C main */
    bl main

hang:
    b hang
