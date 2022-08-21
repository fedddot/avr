#ifndef _GPIO_H_
#  define _GPIO_H_

#include <stdio.h>
#include "register.h"

namespace GPIO {

    enum RegistersStatus {
        REGS_OK = 0,
        REGS_UNSET = -1
    };  

    enum PinCfg {
        PIN_CFG_INPUT_HiZ = 0,
        PIN_CFG_INPUT_PU = 1,
        PIN_CFG_OUTPUT = 2,
        PIN_CFG_UNREACHABLE = -1,
        PIN_CFG_IMPOSSIBLE = -2,
        PIN_CFG_INCORRECT = -3
    };

    enum PUStatus {
        PU_DISABLED = 0,
        PU_ENABLED = 1,
        PU_UNREACHABLE = -1
    };

    class GPIO {
    protected:
        // protected objects fields
        // TODO: Make it static
        Register::Register mcucr;
        Register::BitNumber pud_bit;

        Register::Register port;
        Register::Register ddr;
        Register::Register pin;
    public:
        // constructors
        GPIO();
        GPIO(Register::Register port_reg, Register::Register ddr_reg, Register::Register pin_reg);

        // public methods
        //  status
        RegistersStatus GetRegistersStatus(void);
        PUStatus GetPUStatus(void);
        //  configuration
        PinCfg set_pin_cfg(Register::BitNumber pin_number, PinCfg pin_cfg);
        PinCfg get_pin_cfg(Register::BitNumber pin_number);

        //  i/o operations
        Register::BitValue set_pin(Register::BitNumber pin_number, Register::BitValue value);
        Register::BitValue get_pin(Register::BitNumber pin_number);

        //  getters/setters
        Register::Register get_port_reg(void);
        void set_port_reg(Register::Register port_reg);
        Register::Register get_ddr_reg(void);
        void set_ddr_reg(Register::Register ddr_reg);
        Register::Register get_pin_reg(void);
        void set_pin_reg(Register::Register pin_reg);
        
        Register::Register get_mcucr_reg(void);
        void set_mcucr_reg(Register::Register mcucr_reg);
        Register::BitNumber get_pud_bit(void);
        void set_pud_bit(Register::BitNumber pud_bit_num);
    };    
}               

#endif // _GPIO_H_