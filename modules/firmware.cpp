#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

char status_str[] = "Controller status:\n\
\tbuff capacity = %u\n\
\tbuff size = %u\n\
\tuart receiver status = %d\n";

int main() {
    UART uart = UART();
    uart_receiver_status_t receiver_status = UART_RECEIVER_FAILURE;
    char *dest = (char *)malloc(BUFF_LEN * sizeof(char));
    size_t bufsize = 0;

    receiver_status = uart.start_receiver(BUFF_LEN);
    
    while (1) {
        clean_buff(dest, BUFF_LEN);

        sprintf(
            dest, 
            status_str, 
            uart.get_buffer_capacity(), 
            uart.get_buffer_size(), 
            (int)receiver_status
        );

        uart.send_bytes(dest, strlen(dest));    

        _delay_ms(1000);
    }

    

    return 0;
}