#include <avr/io.h>
#include <alloca.h>
#include <util/delay.h>
#include <string.h>

#include "uart.h"

#define WPINNUM 5
#define WPORT PORTB
#define WDDR DDRB
#define WPIN PINB

#define ASCII_0 0x30
#define ASCII_9 0x39
#define ASCII_A 0x41
#define ASCII_Z 0x5A

#define BASE_10 10

#define ASCII_LEN 128


char *ItoaAnyBaseRecursive(int value, char *str, unsigned int radix)
{
    if ((value < (int)radix) && (value > -(int)radix))
    {
        if (value < 0)
        {
            *str = '-';
            ++str;
        }      
    }
    else
    {
        str = ItoaAnyBaseRecursive(value / (int)radix, str, radix);
        value = value % (int)radix;
    } 
    if (value < 0)
    {
        value = -value;
    }
    if (value < BASE_10)
    {
        *str = (char)value + ASCII_0;
    }
    else
    {
        *str = (char)value - BASE_10 + ASCII_A;
    }
    return str + 1;  
}

char *ItoaBaseTen(int value, char *str)
{
    char *str_end = NULL;

    str_end = ItoaAnyBaseRecursive(value, str, 10);
    *str_end = '\0';
    return str;
}


int main() {
    char *data = (char *)alloca(20);

    UART uart = UART();

    WDDR |= 1 << WPINNUM;
    
    while (1)
    {
        WPORT |= 1 << WPINNUM;
        _delay_ms(1000);

        data = strcpy(data, "baud: ");
        uart.send_bytes((uint8_t *)data, strlen(data));
        data = ItoaBaseTen((int)uart.get_baud_rate(), data);
        uart.send_bytes((uint8_t *)data, strlen(data));
        data = strcpy(data, "\n");
        uart.send_bytes((uint8_t *)data, strlen(data));
        WPORT &= ~(1 << WPINNUM);
        _delay_ms(1000);
    }

    return 0;
}