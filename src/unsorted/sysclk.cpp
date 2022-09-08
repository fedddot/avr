#include "sysclk.h" /* header file */

// constructors

SysCLK::SysCLK() {

}

SysCLK::SysCLK(clk_freq_t _f_osc, 
               FUSELowReg _fuse_low, 
               CLKPReg _clkpr) {
    set_f_osc(_f_osc);
    set_fuse_low(_fuse_low);
    set_clkpr(_clkpr);
}

// public methods

clk_freq_t SysCLK::get_clk_sys(void) {
    if (FUSE_BIT_VAL_PROGRAMMED == fuse_low.get_fuse_bit(FUSE_LOW_CKDIV8)) {
        return f_osc >> 3;
    } else {
        return f_osc;
    }
}

clk_freq_t SysCLK::get_clk_cpu(void) {
    return get_clk_sys() >> clkpr.get_prescaler();
}

clk_freq_t SysCLK::get_clk_io(void) {
    // TODO: Research on the feature
    return get_clk_cpu();
}

clk_freq_t SysCLK::get_clk_flash(void) {
    // TODO: Research on the feature
    return get_clk_cpu();
}

clk_freq_t SysCLK::get_clk_asy(void) {
    // TODO: Research on the feature
    return get_clk_cpu();
}

clk_freq_t SysCLK::get_clk_adc(void) {
    // TODO: Research on the feature
    return get_clk_cpu();
}

//  getters/setters

clk_freq_t SysCLK::get_f_osc(void) {
    return f_osc;
}

void SysCLK::set_f_osc(clk_freq_t _f_osc) {
    f_osc = _f_osc;
}

FUSELowReg SysCLK::get_fuse_low(void) {
    return fuse_low;
}

void SysCLK::set_fuse_low(FUSELowReg _fuse_low) {
    fuse_low = _fuse_low;
}

CLKPReg SysCLK::get_clkpr(void) {
    return clkpr;
}

void SysCLK::set_clkpr(CLKPReg _clkpr) {
    clkpr = _clkpr;
}