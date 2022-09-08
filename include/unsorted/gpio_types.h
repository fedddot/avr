#ifndef _GPIO_TYPES_H_
#define _GPIO_TYPES_H_

#include "register.h" // Register

enum gpio_status {
    GPIO_READY = 0,
    GPIO_NOT_READY = -1
};  

enum gpio_pin_cfg {
    GPIO_PIN_CFG_INPUT_HiZ = 0,
    GPIO_PIN_CFG_INPUT_PU = 1,
    GPIO_PIN_CFG_OUTPUT = 2,
    GPIO_PIN_CFG_UNDEFINED = -1
};

struct gpio_params_struct {
    Register mcucr;
    reg_bit_number_t pud;
    Register port;
    Register ddr;
    Register pin;
};

#endif // _GPIO_TYPES_H_