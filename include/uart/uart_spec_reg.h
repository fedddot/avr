#ifndef _UART_SPEC_REG_H_
#define _UART_SPEC_REG_H_

#include "register.h" // Register

enum ucsra_bits {
    UCSRA_MPCM = 0,
    UCSRA_U2X = 1,
    UCSRA_UPE = 2,
    UCSRA_DOR = 3,
    UCSRA_FE = 4,
    UCSRA_UDRE = 5,
    UCSRA_TXC = 6,
    UCSRA_RXC = 7
};

enum ucsrb_bits {
    UCSRB_TXB8 = 0,
    UCSRB_RXB8 = 1,
    UCSRB_UCSZ2 = 2,
    UCSRB_TXEN = 3,
    UCSRB_RXEN = 4,
    UCSRB_UDRIE = 5,
    UCSRB_TXCIE = 6,
    UCSRB_RXCIE = 7,
};

enum ucsrc_bits {
    UCSRC_UCPOL = 0,
    UCSRC_UCSZ0 = 1,
    UCSRC_UCSZ1 = 2,
    UCSRC_USBS = 3,
    UCSRC_UPM0 = 4,
    UCSRC_UPM1 = 5,
    UCSRC_UMSEL0 = 6,
    UCSRC_UMSEL1 = 7,
};

// TODO: Update addreses

Register UCSR0A((reg_t *)0x100);
Register UCSR0B((reg_t *)0x100);
Register UCSR0C((reg_t *)0x100);
Register UBRR0H((reg_t *)0x100);
Register UBRR0L((reg_t *)0x100);
Register UDR0((reg_t *)0x100);

#endif // _UART_SPEC_REG_H_