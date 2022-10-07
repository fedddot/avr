#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "uart.h"
#include "circbuff.h"

#define WPINNUM 5
#define WPORT PORTB
#define WDDR DDRB
#define WPIN PINB

#define BUFF_LEN 10

UART uart = UART();
CircularBuffer buff = CircularBuffer(BUFF_LEN);

char dest[BUFF_LEN] = { 0 };

int main() {


    WDDR |= 1 << WPINNUM;

    uart.start_receiver(&buff);
    
    while (1)
    {
        WPORT |= 1 << WPINNUM;
        _delay_ms(1000);
        WPORT &= ~(1 << WPINNUM);
        _delay_ms(1000);
        
        if (0 < buff.read_bytes(dest, BUFF_LEN)) {
            uart.send_bytes((const char *)dest, BUFF_LEN);
            buff.flush_buff();
        }
    }

    return 0;
}