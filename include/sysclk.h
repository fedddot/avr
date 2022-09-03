#ifndef _SYSCLK_H_
#define _SYSCLK_H_

#include <inttypes.h> // int32_t

#include "register.h" // Register
#include "fuses.h" // fuse_feature_status_t
#include "mcu_spreg.h" // CLKPReg

typedef uint32_t sysclk_freq_t;

class SysCLK {
protected:
    sysclk_freq_t f_osc;
    FUSELowReg fuse_low;
    CLKPReg clkpr;
public:
    // constructors

    SysCLK();
    SysCLK(sysclk_freq_t _f_osc, 
           FUSELowReg _fuse_low, 
           CLKPReg _clkpr);

    // public methods

    // clk_sys = (ENABLED == fuse_presc8_status) ? (f_osc / 8) : f_osc
    sysclk_freq_t get_clk_sys(void);
    // clk_cpu = clk_sys / prescaler (clkpr)
    sysclk_freq_t get_clk_cpu(void);
    sysclk_freq_t get_clk_io(void);
    sysclk_freq_t get_clk_flash(void);
    sysclk_freq_t get_clk_asy(void);
    sysclk_freq_t get_clk_adc(void);

    //  getters/setters
    sysclk_freq_t get_f_osc(void);
    void set_f_osc(sysclk_freq_t _fosc);

    FUSELowReg get_fuse_low(void);
    void set_fuse_low(FUSELowReg _fuse_low);

    CLKPReg get_clkpr(void);
    void set_clkpr(CLKPReg _clkpr);
};              

#endif // _SYSCLK_H_