#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include "uart.h"
#include "circbuff.h"

#define WPINNUM 5
#define WPORT PORTB
#define WDDR DDRB
#define WPIN PINB

#define BUFF_LEN 100

void clean_buff(char *buff, size_t buff_size) {
    char *buff_end = buff + buff_size;
    while (buff_end > buff) {
        *buff = 0;
        ++buff;
    }
}

int main() {
    UART uart = UART();
    CircularBuffer buff = CircularBuffer(BUFF_LEN);
    char *dest = (char *)malloc(BUFF_LEN * sizeof(char));
    size_t dest_actual_size = 0;

    char str[] = "Last buff read: ";

    WDDR |= 1 << WPINNUM;

    uart.start_receiver(&buff);

    buff.flush();
    


    while (1)
    {
        WPORT |= 1 << WPINNUM;
        _delay_ms(1000);
        WPORT &= ~(1 << WPINNUM);
        _delay_ms(1000);
        
        dest_actual_size = buff.read_bytes(dest, BUFF_LEN);
        uart.send_bytes((const char *)str, strlen(str));
        uart.send_bytes((const char *)dest, BUFF_LEN);
        uart.send_bytes("\n", 1);
        buff.flush();
        clean_buff(dest, BUFF_LEN);
    }

    return 0;
}