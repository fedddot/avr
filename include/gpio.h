#ifndef _GPIO_H_
#define _GPIO_H_

#include "register.h" /* Register */
#include "mcu_spreg.h" /* MCUCReg */

typedef enum gpio_regs_status {
    GPIO_REGS_OK = 0,
    GPIO_REGS_UNDEFINED = -1
} gpio_regs_status_t;  

typedef enum gpio_pin_cfg {
    GPIO_PIN_CFG_INPUT_HiZ = 0,
    GPIO_PIN_CFG_INPUT_PU = 1,
    GPIO_PIN_CFG_OUTPUT = 2,
    GPIO_PIN_CFG_UNDEFINED = -1
} gpio_pin_cfg_t;

class GPIO {
protected:
    // TODO: find a way to do it static
    MCUCReg mcucr_reg;
    // protected object fields
    Register port_reg;
    Register ddr_reg;
    Register pin_reg;
public:
    // constructors
    GPIO();
    GPIO(Register _port_reg, Register _ddr_reg, Register _pin_reg);

    // public methods
    //  status
    gpio_regs_status_t get_registers_status(void);
    //  configuration
    gpio_pin_cfg_t set_pin_cfg(reg_bit_number_t _pin_number, gpio_pin_cfg_t _pin_cfg);
    gpio_pin_cfg_t get_pin_cfg(reg_bit_number_t _pin_number);

    //  i/o operations
    reg_bit_value_t set_pin(reg_bit_number_t _pin_number, reg_bit_value_t _value);
    reg_bit_value_t get_pin(reg_bit_number_t _pin_number);

    //  getters/setters
    Register get_port_reg(void);
    void set_port_reg(Register _port_reg);

    Register get_ddr_reg(void);
    void set_ddr_reg(Register _ddr_reg);

    Register get_pin_reg(void);
    void set_pin_reg(Register _pin_reg);
    
    // TODO: find a way to do it static
    void set_mcucr_reg(MCUCReg _mcucr_reg);
    MCUCReg get_mcucr_reg(void);
};    

#endif // _GPIO_H_