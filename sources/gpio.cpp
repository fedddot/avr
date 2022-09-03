#include "gpio.h"


// constructors
GPIO::GPIO() {
    // default constructor
}

GPIO::GPIO(Register _port_reg, Register _ddr_reg, Register _pin_reg) {
    set_port_reg(_port_reg);
    set_ddr_reg(_ddr_reg);
    set_pin_reg(_pin_reg);
}

// public methods
// status
gpio_regs_status_t GPIO::get_registers_status(void) {
    if (NULL == mcucr_reg.get_register_ptr())
        return GPIO_REGS_UNDEFINED;
    if (NULL == port_reg.get_register_ptr())
        return GPIO_REGS_UNDEFINED;
    if (NULL == ddr_reg.get_register_ptr())
        return GPIO_REGS_UNDEFINED;
    if (NULL == pin_reg.get_register_ptr())
        return GPIO_REGS_UNDEFINED;
    return GPIO_REGS_OK;
}

//  configuration
gpio_pin_cfg_t GPIO::set_pin_cfg(reg_bit_number_t _pin_number, gpio_pin_cfg_t _pin_cfg) {
    if (GPIO_REGS_UNDEFINED == get_registers_status())
        return GPIO_PIN_CFG_UNDEFINED;

    switch (_pin_cfg) {
        case GPIO_PIN_CFG_INPUT_HiZ:
            ddr_reg.set_bit(_pin_number, BIT_LOW);
            port_reg.set_bit(_pin_number, BIT_LOW);
            return GPIO_PIN_CFG_INPUT_HiZ;

        case GPIO_PIN_CFG_INPUT_PU:
            if (GPIO_PU_ENABLED != get_pu_status())
                return GPIO_PIN_CFG_UNDEFINED;
            ddr_reg.set_bit(_pin_number, BIT_LOW);
            port_reg.set_bit(_pin_number, BIT_HIGH);
            return GPIO_PIN_CFG_INPUT_PU;

        case GPIO_PIN_CFG_OUTPUT:
            ddr_reg.set_bit(_pin_number, BIT_HIGH);
            port_reg.set_bit(_pin_number, BIT_LOW);
            return GPIO_PIN_CFG_OUTPUT;

        default:
            break;
    }
    return GPIO_PIN_CFG_UNDEFINED;
}

gpio_pin_cfg_t GPIO::get_pin_cfg(reg_bit_number_t _pin_number) {
    if (GPIO_REGS_UNDEFINED == get_registers_status())
        return GPIO_PIN_CFG_UNDEFINED;    

    switch (ddr_reg.get_bit(_pin_number)) {
    // pin configured as input
    case BIT_LOW:
        switch (port_reg.get_bit(_pin_number)) {
        // HiZ
        case BIT_LOW:
            return GPIO_PIN_CFG_INPUT_HiZ;
        // Pulled-Up - need to check PUD bit
        case BIT_HIGH:
            if (GPIO_PU_ENABLED == get_pu_status())
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
    return port_reg.set_bit(_pin_number, _value);
}

reg_bit_value_t GPIO::get_pin(reg_bit_number_t _pin_number) {
    return pin_reg.get_bit(_pin_number);
}

//  getters/setters
Register GPIO::get_port_reg(void) {
    return port_reg;
}

void GPIO::set_port_reg(Register _port_reg) {
    port_reg = _port_reg;
}

Register GPIO::get_ddr_reg(void) {
    return ddr_reg;
}

void GPIO::set_ddr_reg(Register _ddr_reg) {
    ddr_reg = _ddr_reg;
}

Register GPIO::get_pin_reg(void) {
    return pin_reg;
}

void GPIO::set_pin_reg(Register _pin_reg) {
    pin_reg = _pin_reg;
}

// static public methods
void GPIO::set_mcucr_reg(Register _mcucr_reg, reg_bit_number_t _pud_bit) {
    mcucr_reg = _mcucr_reg;
    pud_bit = _pud_bit;
}

Register GPIO::get_mcucr_reg(void) {
    return mcucr_reg;
}

reg_bit_number_t GPIO::get_pud_bit(void) {
    return pud_bit;
}
  
gpio_pu_status_t GPIO::get_pu_status(void) {
    if (NULL == mcucr_reg.get_register_ptr()) {
        return GPIO_PU_UNDEFINED;
    }
    switch (mcucr_reg.get_bit(pud_bit)) {

        case BIT_LOW:
            return GPIO_PU_ENABLED;

        case BIT_HIGH:
            return GPIO_PU_DISABLED;
        
        default:
            break;
    }
    return GPIO_PU_UNDEFINED;
}

gpio_pu_status_t GPIO::set_pu_status(gpio_pu_status_t _pu_status) {
    if (NULL == mcucr_reg.get_register_ptr()) {
        return GPIO_PU_UNDEFINED;
    }
    switch (_pu_status) {
    case GPIO_PU_ENABLED:
        if (BIT_LOW == mcucr_reg.set_bit(pud_bit, BIT_LOW))
            return GPIO_PU_ENABLED;
        break;
    case GPIO_PU_DISABLED:
        if (BIT_HIGH == mcucr_reg.set_bit(pud_bit, BIT_HIGH))
            return GPIO_PU_DISABLED;
        break;        
    default:
        break;
    }
    return GPIO_PU_UNDEFINED;
}