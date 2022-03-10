#include "led.h"

#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#define BLINK_LED_MS 500

void led_blink() {
    DDRB |= _BV(PORTB1);  // Put the B1 in output mode
    while (1) {
        PORTB ^= _BV(PORTB1);     // Toggle the LED
        _delay_ms(BLINK_LED_MS);  // Delay the LED 500ms
    }
}
char theChar;
void led_uart() {  // Communication with the LED via screen
    theChar = uart_getchar();
    if (theChar == 'O') {
        theChar = uart_getchar();
        if (theChar == 'N') {
            theChar = uart_getchar();
            if (theChar == '\r') {
                theChar = uart_getchar();
                if (theChar == '\n') {
                    PORTB &= ~_BV(PORTB1);
                }
            }
        } else if (theChar == 'F') {
            theChar = uart_getchar();
            if (theChar == 'F') {
                theChar = uart_getchar();
                if (theChar == '\r') {
                    theChar = uart_getchar();
                    if (theChar == '\n') {
                        PORTB |= _BV(PORTB1);
                    }
                }
            }
        }
    }
}
