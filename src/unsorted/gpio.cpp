#include <stddef.h> // NULL

#include "gpio.h" // interface

//  constructors

GPIO::GPIO() {
    // default constructor
}

GPIO::GPIO(gpio_params_t _gpio_params) {
    set_gpio_params(_gpio_params);
}

//  configuration

gpio_pin_cfg_t GPIO::set_pin_cfg(reg_bit_number_t _pin_number, gpio_pin_cfg_t _pin_cfg) {
    if (GPIO_NOT_READY == get_registers_status())
        return GPIO_PIN_CFG_UNDEFINED;

    switch (_pin_cfg) {
        case GPIO_PIN_CFG_INPUT_HiZ:
            gpio_params.ddr.set_bit(_pin_number, BIT_LOW);
            gpio_params.port.set_bit(_pin_number, BIT_LOW);
            return GPIO_PIN_CFG_INPUT_HiZ;

        case GPIO_PIN_CFG_INPUT_PU:
            if (BIT_LOW != gpio_params.mcucr.get_bit(gpio_params.pud))
                return GPIO_PIN_CFG_UNDEFINED;
            gpio_params.ddr.set_bit(_pin_number, BIT_LOW);
            gpio_params.port.set_bit(_pin_number, BIT_HIGH);
            return GPIO_PIN_CFG_INPUT_PU;

        case GPIO_PIN_CFG_OUTPUT:
            gpio_params.ddr.set_bit(_pin_number, BIT_HIGH);
            gpio_params.port.set_bit(_pin_number, BIT_LOW);
            return GPIO_PIN_CFG_OUTPUT;

        default:
            break;
    }
    return GPIO_PIN_CFG_UNDEFINED;
}

gpio_pin_cfg_t GPIO::get_pin_cfg(reg_bit_number_t _pin_number) {
    if (GPIO_NOT_READY == get_registers_status())
        return GPIO_PIN_CFG_UNDEFINED;    

    switch (gpio_params.ddr.get_bit(_pin_number)) {
    // pin configured as input
    case BIT_LOW:
        switch (gpio_params.port.get_bit(_pin_number)) {
        // HiZ
        case BIT_LOW:
            return GPIO_PIN_CFG_INPUT_HiZ;
        // Pulled-Up - need to check PUD bit
        case BIT_HIGH:
            if (BIT_LOW != gpio_params.mcucr.get_bit(gpio_params.pud))
                return GPIO_PIN_CFG_INPUT_PU;
            return GPIO_PIN_CFG_UNDEFINED;      
        default:
            return GPIO_PIN_CFG_UNDEFINED;
        }
    // pin configured as output
    case BIT_HIGH:
        return GPIO_PIN_CFG_OUTPUT;
    // ddr unreachable
    default:
        return GPIO_PIN_CFG_UNDEFINED;
    }
    return GPIO_PIN_CFG_UNDEFINED;
}

//  i/o operations

reg_bit_value_t GPIO::set_pin(reg_bit_number_t _pin_number, reg_bit_value_t _value) {
    if (GPIO_PIN_CFG_OUTPUT != get_pin_cfg(_pin_number))
        return BIT_UNDEFINED;
    return gpio_params.port.set_bit(_pin_number, _value);
}

reg_bit_value_t GPIO::get_pin(reg_bit_number_t _pin_number) {
    return gpio_params.pin.get_bit(_pin_number);
}

//  getters/setters

void GPIO::set_gpio_params(gpio_params_t _gpio_params) {
    gpio_params = _gpio_params;
}

gpio_params_t GPIO::get_gpio_params(void) {
    return gpio_params;
}

//  status

gpio_status_t GPIO::get_registers_status(void) {
    if (NULL == gpio_params.port.get_register_ptr())
        return GPIO_NOT_READY;
    if (NULL == gpio_params.ddr.get_register_ptr())
        return GPIO_NOT_READY;
    if (NULL == gpio_params.pin.get_register_ptr())
        return GPIO_NOT_READY;
    if (NULL == gpio_params.mcucr.get_register_ptr())
        return GPIO_NOT_READY;
    return GPIO_READY;
}