#include <stdio.h>
#include "register.h"
#include "gpio.h"

int main() {
    uint8_t MCUCR = 0;
    uint8_t PORTA = 0;
    uint8_t DDRA = 0;
    uint8_t PINA = 0;
    Register::BitNumber pud_bit = Register::BIT2;

    GPIO::GPIO gpio = GPIO::GPIO(
        Register::Register(&PORTA),
        Register::Register(&DDRA),
        Register::Register(&PINA)
    );    
    gpio.set_mcucr_reg(
        Register::Register(&MCUCR)
    );
    gpio.set_pud_bit(pud_bit);
    //gpio.get_mcucr_reg().set_bit(pud_bit, Register::BIT_HIGH);

    printf("pud_bit = %d\n", gpio.get_pud_bit());
    printf("PUstatus = %d\n", gpio.GetPUStatus());

    printf("cfg result = %d\n", gpio.set_pin_cfg(Register::BIT1, GPIO::PIN_CFG_INPUT_PU));
    printf("MCUCR = %d; PORTA = %d; DDRA = %d; PINA = %d;\n", MCUCR, PORTA, DDRA, PINA);


    return 0;
}