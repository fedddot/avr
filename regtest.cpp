#include <stdio.h>
#include "register.h"

int main() {
    uint8_t TREG = 0;
    Register::Register reg;    

    printf("Trying to set a bit in reg. Returned = %d\n", reg.set_bit(Register::BIT7, Register::HIGH));
    printf("Trying to get a bit in reg. Returned = %d\n", reg.get_bit(Register::BIT7));
    printf("TREG = %d\n", TREG);
    reg.set_register_ptr(&TREG);
    printf("Trying to set a bit in reg. Returned = %d\n", reg.set_bit(Register::BIT7, Register::HIGH));
    printf("Trying to get a bit in reg. Returned = %d\n", reg.get_bit(Register::BIT7));
    printf("TREG = %d\n", TREG);

    return 0;
}