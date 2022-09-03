#include "sysclk.h" /* header file */

#define _SYSCLK_CLKPS3_CLKPS0_MASK_ 0x0F
#define _SYSCLK_MAX_PRESC_SHIFTS_ 8
#define _SYSCLK_DEFAULT_F_OSC_ 8000000
#define _SUSCLK_DEFAULT_FUSE_PRESC8_ FUSE_FEATURE_ENABLED


// constructors

SysCLK::SysCLK() {
    set_f_osc(_SYSCLK_DEFAULT_F_OSC_);
    set_fuse_presc8_status(_SUSCLK_DEFAULT_FUSE_PRESC8_);
}

SysCLK::SysCLK(sysclk_freq_t _f_osc, fuse_feature_status_t _fuse_presc8_status, Register _clkpr) {
    set_f_osc(_f_osc);
    set_fuse_presc8_status(_fuse_presc8_status);
    set_clkpr(_clkpr);
}

// public methods

sysclk_freq_t SysCLK::get_clk_sys(void) {
    if (FUSE_FEATURE_ENABLED == fuse_presc8_status) {
        return f_osc >> 3;
    } else {
        return f_osc;
    }
}

sysclk_freq_t SysCLK::get_clk_cpu(void) {
    uint8_t shifts = 0;
    shifts = *clkpr.get_register_ptr() & ((reg_t)_SYSCLK_CLKPS3_CLKPS0_MASK_);
    if (shifts > _SYSCLK_MAX_PRESC_SHIFTS_)
        return 0;
    return get_clk_sys() >> shifts;
}

sysclk_freq_t SysCLK::get_clk_io(void) {
    // TODO: Research on the feature
    return get_clk_cpu();
}

sysclk_freq_t SysCLK::get_clk_flash(void) {
    // TODO: Research on the feature
    return get_clk_cpu();
}

sysclk_freq_t SysCLK::get_clk_asy(void) {
    // TODO: Research on the feature
    return get_clk_cpu();
}

sysclk_freq_t SysCLK::get_clk_adc(void) {
    // TODO: Research on the feature
    return get_clk_cpu();
}

//  getters/setters

sysclk_freq_t SysCLK::get_f_osc(void) {
    return f_osc;
}

void SysCLK::set_f_osc(sysclk_freq_t _f_osc) {
    f_osc = _f_osc;
}

fuse_feature_status_t SysCLK::get_fuse_presc8_status(void) {
    return fuse_presc8_status;
}

void SysCLK::set_fuse_presc8_status(fuse_feature_status_t _fuse_presc8_status) {
    fuse_presc8_status = _fuse_presc8_status;
}

Register SysCLK::get_clkpr(void) {
    return clkpr;
}

void SysCLK::set_clkpr(Register _clkpr) {
    clkpr = _clkpr;
}