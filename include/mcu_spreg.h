#ifndef _MCU_SPREG_H_
#define _MCU_SPREG_H_

#include "register.h" /* Register */
 
typedef enum sreg_bit_number {
    SREG_BIT_C = BIT0,
    SREG_BIT_Z = BIT1,
    SREG_BIT_N = BIT2,
    SREG_BIT_V = BIT3,
    SREG_BIT_S = BIT4,
    SREG_BIT_H = BIT5,
    SREG_BIT_T = BIT6,
    SREG_BIT_I = BIT7
} sreg_bit_number_t;

typedef enum mcucr_bit_number {
    MCUCR_BIT_PUD = BIT4
} mcucr_bit_number_t;

typedef enum clkpr_bit_number {
    CLKPR_BIT_CLKPS0 = BIT0,
    CLKPR_BIT_CLKPS1 = BIT1,
    CLKPR_BIT_CLKPS2 = BIT2,
    CLKPR_BIT_CLKPS3 = BIT3,
    CLKPR_BIT_CLKPCE = BIT7
} clkpr_bit_number_t;

class SReg: Register {
public:
    SReg();
    SReg(reg_t *_sreg_ptr);
    
    reg_bit_value_t sei(void);
    reg_bit_value_t cli(void);
    reg_bit_value_t gei(void);
};

class MCUCReg: Register {
public:
    MCUCReg();
    MCUCReg(reg_t *_mcucr_ptr);
    reg_bit_value_t get_pud(void);
    reg_bit_value_t set_pud(reg_bit_value_t _val);
};

class CLKPReg: Register {
public:
    CLKPReg();
    CLKPReg(reg_t *_clkpr_ptr);
    reg_t get_prescaler(void);
    reg_t set_prescaler(reg_t prescaler);
};

#endif // _MCU_SPREG_H_
