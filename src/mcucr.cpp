#include "mcucr.h"

// constructors
MCUCReg::MCUCReg(): Register() {
    // Default constructor
}

MCUCReg::MCUCReg(reg_t *_mcucr_ptr): Register(_mcucr_ptr) {

}

// public methods
reg_bit_value_t MCUCReg::get_pud(void) {
    return get_bit(
        (reg_bit_number_t)MCUCR_BIT_PUD
    );
}

reg_bit_value_t MCUCReg::set_pud(reg_bit_value_t _val) {
    return set_bit(
        (reg_bit_number_t)MCUCR_BIT_PUD, _val
    );
}
