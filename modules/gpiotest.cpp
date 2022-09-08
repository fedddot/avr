#include <stdio.h>

#include "register.h"
#include "gpio.h"

reg_t MCUCR = 0; reg_bit_number_t PUD = BIT4;
reg_t PORTA = 0;
reg_t DDRA = 0;
reg_t PINA = 0;

void PrintRegisters(void);
void set_pin_cfg_test(GPIO gpio);

int main() {
    gpio_params_t params = {
        Register(&MCUCR), PUD,
        Register(&PORTA), Register(&DDRA), Register(&PINA) 
    };

    GPIO gpio = GPIO(params);
    set_pin_cfg_test(gpio);

    return 0;
}

void PrintRegisters(void) {
    printf("\t\tMCUCR = 0x%x, PUD = 0x%x,\n", MCUCR, PUD);
    printf("\t\tPORTA = 0x%x, DDRA = 0x%x, PINA = 0x%x,\n", PORTA, DDRA, PINA);
}

void set_pin_cfg_test(GPIO gpio) {
    reg_bit_number_t bit;
    gpio_pin_cfg_t cfg;
    printf("set_pin_cfg_test\n");
    printf("\tRegisters before changes:\n");
    PrintRegisters();

    bit = BIT4; cfg = GPIO_PIN_CFG_INPUT_PU;
    printf("\tgpio.set_pin_cfg(%d, %d) = %d\n", bit, cfg, gpio.set_pin_cfg(bit, cfg));
    printf("\tregisters after that:\n");
    PrintRegisters();

    bit = BIT4; cfg = GPIO_PIN_CFG_INPUT_HiZ;
    printf("\tgpio.set_pin_cfg(%d, %d) = %d\n", bit, cfg, gpio.set_pin_cfg(bit, cfg));
    printf("\tregisters after that:\n");
    PrintRegisters();    
}
