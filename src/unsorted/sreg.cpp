#include "sreg.h"

// constructors
SReg::SReg(): Register() {
    // Default constructor
}

SReg::SReg(reg_t *_sreg_ptr): Register(_sreg_ptr) {

}

// public methods
reg_bit_value_t SReg::sei(void) {
    return set_bit(
        (reg_bit_number_t)SREG_BIT_I, 
        BIT_HIGH
    );
}

reg_bit_value_t SReg::cli(void) {
    return set_bit(
        (reg_bit_number_t)SREG_BIT_I, 
        BIT_LOW
    );
}

reg_bit_value_t SReg::gei(void) {
    return get_bit(
        (reg_bit_number_t)SREG_BIT_I
    );
}


