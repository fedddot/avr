#include "gpio.h"

// protected methods
GPIO::RegistersStatus GPIO::GPIO::GetRegistersStatus(void) {
    // if (NULL == mcucr.get_register_ptr())
    //     return REGS_UNSET;
    // if (NULL == port.get_register_ptr())
    //     return REGS_UNSET;
    // if (NULL == ddr.get_register_ptr())
    //     return REGS_UNSET;
    // if (NULL == pin.get_register_ptr())
    //     return REGS_UNSET;
    return REGS_OK;
}

GPIO::PUStatus GPIO::GPIO::GetPUStatus(void) {
    // switch (mcucr.get_bit(pud_bit)) {

    //     case Register::BIT_LOW:
    //         return PU_ENABLED;

    //     case Register::BIT_HIGH:
    //         return PU_DISABLED;
        
    //     default:
    //         return PU_UNREACHABLE;
    // }
    return PU_ENABLED;
}

// constructors
GPIO::GPIO::GPIO() {
    // default constructor
}

GPIO::GPIO::GPIO(Register::Register port_reg, Register::Register ddr_reg, Register::Register pin_reg) {
    set_port_reg(port_reg);
    set_ddr_reg(ddr_reg);
    set_pin_reg(pin_reg);
}

// public methods
//  configuration
GPIO::PinCfg GPIO::GPIO::set_pin_cfg(Register::BitNumber pin_number, PinCfg pin_cfg) {
    if (REGS_UNSET == GetRegistersStatus())
        return PIN_CFG_UNREACHABLE;

    switch (pin_cfg) {
        case PIN_CFG_INPUT_HiZ:
            ddr.set_bit(pin_number, Register::BIT_LOW);
            port.set_bit(pin_number, Register::BIT_LOW);
            return PIN_CFG_INPUT_HiZ;

        case PIN_CFG_INPUT_PU:
            if (PU_DISABLED == GetPUStatus())
                return PIN_CFG_IMPOSSIBLE;
            ddr.set_bit(pin_number, Register::BIT_LOW);
            port.set_bit(pin_number, Register::BIT_HIGH);
            return PIN_CFG_INPUT_PU;

        case PIN_CFG_OUTPUT:
            ddr.set_bit(pin_number, Register::BIT_HIGH);
            port.set_bit(pin_number, Register::BIT_LOW);
            return PIN_CFG_OUTPUT;

        default:
            return PIN_CFG_INCORRECT;
    }
}

GPIO::PinCfg GPIO::GPIO::get_pin_cfg(Register::BitNumber pin_number) {
    if (REGS_UNSET == GetRegistersStatus())
        return PIN_CFG_UNREACHABLE;    

    switch (ddr.get_bit(pin_number))
    {
    // pin configured as input
    case Register::BIT_LOW:
        switch (port.get_bit(pin_number))
        {
        // HiZ
        case Register::BIT_LOW:
            return PIN_CFG_INPUT_HiZ;
        // Pulled-Up - need to check PUD bit
        case Register::BIT_HIGH:
            if (PU_DISABLED == GetPUStatus())
                return PIN_CFG_IMPOSSIBLE;
            return PIN_CFG_INPUT_PU;      
        // port unreachable  
        default:
            return PIN_CFG_UNREACHABLE;
        }
    // pin configured as output
    case Register::BIT_HIGH:
        return PIN_CFG_OUTPUT;
    // ddr unreachable
    default:
        return PIN_CFG_UNREACHABLE;
    }
}

//  i/o operations
Register::BitValue GPIO::GPIO::set_pin(Register::BitNumber pin_number, Register::BitValue value) {
    if (PIN_CFG_OUTPUT != get_pin_cfg(pin_number))
        return Register::BIT_READ_ONLY;
    return port.set_bit(pin_number, value);
}

Register::BitValue GPIO::GPIO::get_pin(Register::BitNumber pin_number) {
    return pin.get_bit(pin_number);
}

//  getters/setters
Register::Register GPIO::GPIO::get_port_reg(void) {
    return port;
}
void GPIO::GPIO::set_port_reg(Register::Register port_reg) {
    port = port_reg;
}
Register::Register GPIO::GPIO::get_ddr_reg(void) {
    return ddr;
}
void GPIO::GPIO::set_ddr_reg(Register::Register ddr_reg) {
    ddr = ddr_reg;
}
Register::Register GPIO::GPIO::get_pin_reg(void) {
    return pin;
}
void GPIO::GPIO::set_pin_reg(Register::Register pin_reg) {
    pin = pin_reg;
}

// static public methods
Register::Register GPIO::GPIO::get_mcucr_reg(void) {
    return mcucr;
}
void GPIO::GPIO::set_mcucr_reg(Register::Register mcucr_reg) {
    mcucr = mcucr_reg;
}
Register::BitNumber GPIO::GPIO::get_pud_bit(void) {
    return pud_bit;
}
void GPIO::GPIO::set_pud_bit(Register::BitNumber pud_bit) {
    pud_bit = pud_bit;
}