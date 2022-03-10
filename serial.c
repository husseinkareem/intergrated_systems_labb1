// close screen Ctrl-a + K Y
// screen /dev/ttyACM0 38400
// ctl+a+: stuff -> skicka in
#include "serial.h"

#include <avr/io.h>
#include <util/delay.h>

#define BAUD 38400
#define FOSC 16000000

void uart_init(void) {
    UCSR0B |= _BV(TXEN0);  // Enable trasnimtter:

    UCSR0B |= _BV(RXEN0);  // Enable receiver:

    UCSR0C |= _BV(UCSZ01);  // 8N1 mode: (controlled by UCSR0C register, see datasheet ch. 24.12.4 p. 249-250). 8-bit data
    UCSR0C |= _BV(UCSZ00);  // No parity

    UCSR0C &= ~_BV(UPM01) & ~_BV(UPM00);

    UCSR0C &= ~_BV(USBS0);

    uint16_t ubrrn = FOSC / (16 * BAUD) - 1;  // Set baudrate: (see datasheet ch. 24)

    UBRR0 = ubrrn;
}
void uart_putchar(char chr) {
    while (!(UCSR0A & (_BV(UDRE0))))
        ;  // Wait for emtpy transmit buffer.

    UDR0 = chr;  // Start transmission
    if (chr == '\n') {
        uart_putchar('\r');
    }
}
char uart_getchar(void) {
    while (!(UCSR0A & (1 << RXC0)))
        ;  // Wait for data to be received (datasheet 20.7.1)

    return UDR0;  // Get and return received data from buffer (datasheet 20.7.1)
}
void uart_putstr(const char *str) {
    while (*str != '\0') {
        uart_putchar(*str++);
    }
}
void uart_echo(void) {
    uart_putchar(uart_getchar());
}
