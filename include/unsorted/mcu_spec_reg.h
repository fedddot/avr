#ifndef _MCU_SPEC_REG_H_
#define _MCU_SPEC_REG_H_

#include "register.h" // Register<...>
 
typedef enum sreg_bits {
    SREG_C = 0,
    SREG_Z = 1,
    SREG_N = 2,
    SREG_V = 3,
    SREG_S = 4,
    SREG_H = 5,
    SREG_T = 6,
    SREG_I = 7
} sreg_bits_t;

typedef enum mcucr_bits {
    MCUCR_PUD = 4 // TODO: fill that
} mcucr_bits_t;

typedef enum clkpr_bits {
    CLKPR_CLKPS0 = 0,
    CLKPR_CLKPS1 = 1,
    CLKPR_CLKPS2 = 2,
    CLKPR_CLKPS3 = 3,
    CLKPR_CLKPCE = 7
} clkpr_bits_t;

typedef Register<sreg_bits_t> RegSREG;
typedef Register<mcucr_bits_t> RegMCUCR;
typedef Register<clkpr_bits_t> RegCLKPR;

#endif // _MCU_SPEC_REG_H_
