/*
 * Copyright (c) 2025 VDRDrive
 *
 * This software is released under the MIT License.
 * See LICENSE file in the project root for full license information.
 */


#include <stdint.h>

#define PERIPHERAL_BASE 0x3F000000
#define GPIO_BASE       (PERIPHERAL_BASE + 0x200000)
#define UART0_BASE      (PERIPHERAL_BASE + 0x201000)

#define GPFSEL1     (*(volatile uint32_t *)(GPIO_BASE + 0x04))
#define GPPUD       (*(volatile uint32_t *)(GPIO_BASE + 0x94))
#define GPPUDCLK0   (*(volatile uint32_t *)(GPIO_BASE + 0x98))

#define UART0_DR    (*(volatile uint32_t *)(UART0_BASE + 0x00))
#define UART0_FR    (*(volatile uint32_t *)(UART0_BASE + 0x18))
#define UART0_IBRD  (*(volatile uint32_t *)(UART0_BASE + 0x24))
#define UART0_FBRD  (*(volatile uint32_t *)(UART0_BASE + 0x28))
#define UART0_LCRH  (*(volatile uint32_t *)(UART0_BASE + 0x2C))
#define UART0_CR    (*(volatile uint32_t *)(UART0_BASE + 0x30))

static void delay(int count) { while (count--) { asm volatile("nop"); } }

void uart_init(void) {
    UART0_CR = 0;  // Disable UART

    /* Setup GPIO14/15 to ALT0 (UART) */
    GPFSEL1 &= ~((7 << 12) | (7 << 15));
    GPFSEL1 |= ((4 << 12) | (4 << 15));

    /* Disable pull-up/down */
    GPPUD = 0;
    delay(150);
    GPPUDCLK0 = (1 << 14) | (1 << 15);
    delay(150);
    GPPUDCLK0 = 0;

    UART0_IBRD = 26;  // Integer part
    UART0_FBRD = 3;   // Fractional part
    UART0_LCRH = (3 << 5); // 8-bit, no parity, 1 stop
    UART0_CR = 0x301;       // Enable TX, RX, UART

}

void uart_send(char c) {
    while (UART0_FR & (1 << 5)) {}
    UART0_DR = c;
}

void uart_puts(const char *s) {
    while (*s) uart_send(*s++);
}

int main(void) {
    uart_init();
    uart_puts("HELLO WORLD FROM RPI 3B+ BARE METAL!\r\n");
    while (1) {
        delay(10000);
        uart_puts("HELLO WORLD FROM RPI 3B+ BARE METAL!\r\n");
    }
    return 0;
}
