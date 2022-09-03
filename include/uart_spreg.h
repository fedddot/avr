#ifndef _UART_SPREG_H_
#define _UART_SPREG_H_

#include "register.h" /* Register, reg_bit_value_t */

typedef enum ucsra_bit_number ucsra_bit_number_t;
typedef enum ucsrb_bit_number ucsrb_bit_number_t;
typedef enum ucsrc_bit_number ucsrc_bit_number_t;

class UCSRegA: Register {
public:
    UCSRegA();
    UCSRegA(reg_t *_ucsra_ptr);
    reg_bit_value_t get_ucsra_bit(ucsra_bit_number_t _ucsra_bit_number);
    reg_bit_value_t set_ucsra_bit(ucsra_bit_number_t _ucsra_bit_number, reg_bit_value_t _val);
};

class UCSRegB: Register {
public:
    UCSRegB();
    UCSRegB(reg_t *_ucsrb_ptr);
    reg_bit_value_t get_ucsrb_bit(ucsrb_bit_number_t _ucsrb_bit_number);
    reg_bit_value_t set_ucsrb_bit(ucsrb_bit_number_t _ucsrb_bit_number, reg_bit_value_t _val);
};

class UCSRegC: Register {
public:
    UCSRegC();
    UCSRegC(reg_t *_ucsrc_ptr);
    reg_bit_value_t get_ucsrc_bit(ucsrc_bit_number_t _ucsrc_bit_number);
    reg_bit_value_t set_ucsrc_bit(ucsrc_bit_number_t _ucsrc_bit_number, reg_bit_value_t _val);
};

enum ucsra_bit_number {
    UCSRA_BIT_MPCM = BIT0,
    UCSRA_BIT_U2X = BIT1,
    UCSRA_BIT_UPE = BIT2,
    UCSRA_BIT_DOR = BIT3,
    UCSRA_BIT_FE = BIT4,
    UCSRA_BIT_UDRE = BIT5,
    UCSRA_BIT_TXC = BIT6,
    UCSRA_BIT_RXC = BIT7,
};
enum ucsrb_bit_number {
    UCSRB_BIT_TXB8 = BIT0,
    UCSRB_BIT_RXB8 = BIT1,
    UCSRB_BIT_UCSZ2 = BIT2,
    UCSRB_BIT_TXEN = BIT3,
    UCSRB_BIT_RXEN = BIT4,
    UCSRB_BIT_UDRIE = BIT5,
    UCSRB_BIT_TXCIE = BIT6,
    UCSRB_BIT_RXCIE = BIT7,
};
enum ucsrc_bit_number {
    UCSRC_BIT_UCPOL = BIT0,
    UCSRC_BIT_UCSZ0 = BIT1,
    UCSRC_BIT_UCSZ1 = BIT2,
    UCSRC_BIT_USBS = BIT3,
    UCSRC_BIT_UPM0 = BIT4,
    UCSRC_BIT_UPM1 = BIT5,
    UCSRC_BIT_UMSEL0 = BIT6,
    UCSRC_BIT_UMSEL1 = BIT7,
};

#endif // _UART_SPREG_H_