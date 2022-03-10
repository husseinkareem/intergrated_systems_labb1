// DEL 4 VG.... För att kompilera: skriv " Make " i terminalen -> " make && screen /dev/ttyACM0 38400 " -> ctrl+a+: -> skriv stuff ON\r\n för att tända leden eller OFF\r\n för att släcka leden. stäng ner screen Ctrl-a + K Y

// uart_putstr("Inside on"); felsökning
#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#define BLINK_LED_MS 500

char strName[] = "husse\n";
char *str_ptr = &strName[0];

int main() {
    DDRB |= _BV(PORTB1);  // Put the B1 in output mode
    PORTB |= _BV(PORTB1);

    // led_blink();          // Deluppgift 1
    // void uart_putchar(char chr);

    uart_init();  // Call the usart initialization

    while (1) {
        // uart_putstr(strName);
        // _delay_ms(500);
        // uart_echo();
        led_uart();
    }
    return 0;
}
