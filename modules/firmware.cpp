#define __AVR_ATmega328P__ 1
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "register.h"
#include "gpio.h"

#define WPIN BIT5


int main() {
    GPIO::GPIO gpio = GPIO::GPIO(
        Register::Register((uint8_t *)&PORTB),
        Register::Register((uint8_t *)&DDRB),
        Register::Register((uint8_t *)&PINB)
    );    
    gpio.set_mcucr_reg(
        Register::Register((uint8_t *)&MCUCR)
    );
    gpio.set_pud_bit(Register::BIT4);
    gpio.set_pin_cfg(Register::BIT5, GPIO::PIN_CFG_OUTPUT);
    gpio.set_pin(Register::BIT5, Register::BIT_LOW);

    while (1)
    {
        gpio.set_pin(Register::BIT5, Register::BIT_LOW);
        _delay_ms(1000);
        gpio.set_pin(Register::BIT5, Register::BIT_HIGH);
        _delay_ms(1000);

    }

    return 0;
}