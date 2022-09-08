//#include <stdio.h>

#include "register.h"

reg_t _REG = 0;

reg_t UCRSA = 0x00;

typedef enum ucsra_bits {
    UCSRA_MPCM = 0,
    UCSRA_U2X,
    UCSRA_UPE,
    UCSRA_DOR,
    UCSRA_FE,
    UCSRA_UDRE,
    UCSRA_TXC,
    UCSRA_RXC
} ucsra_bits_t;

int main() {
    Register<ucsra_bits_t> ucsra = Register<ucsra_bits_t>(&UCRSA);

    return 0;
}