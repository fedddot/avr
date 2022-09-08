#include "mcu_spreg.h" // header file
 
SReg::SReg(): Register() {

}
SReg::SReg(reg_t *_sreg_ptr): Register(_sreg_ptr) {

}
reg_bit_value_t SReg::sei(void) {
    return set_bit((reg_bit_number_t)SREG_BIT_I, BIT_HIGH);
}
reg_bit_value_t SReg::cli(void) {
    return set_bit((reg_bit_number_t)SREG_BIT_I, BIT_LOW);
}
reg_bit_value_t SReg::gei(void) {
    return get_bit((reg_bit_number_t)SREG_BIT_I);
}

MCUCReg::MCUCReg(): Register() {

}
MCUCReg::MCUCReg(reg_t *_mcucr_ptr): Register(_mcucr_ptr) {

}
reg_bit_value_t MCUCReg::get_pud(void) {
    return get_bit((reg_bit_number_t)MCUCR_BIT_PUD);
}
reg_bit_value_t MCUCReg::set_pud(reg_bit_value_t _val) {
    return set_bit((reg_bit_number_t)MCUCR_BIT_PUD, _val);
}


CLKPReg::CLKPReg(): Register() {

}
CLKPReg::CLKPReg(reg_t *_clkpr_ptr): Register(_clkpr_ptr) {

}
reg_t CLKPReg::get_prescaler(void) {
    return (reg_t)(*register_ptr & 0x0F);
}
reg_t CLKPReg::set_prescaler(reg_t prescaler) {
    return get_prescaler();
}

