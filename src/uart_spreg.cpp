#include "uart_spreg.h" /* header file */

UCSRegA::UCSRegA(): Register() {

}
UCSRegA::UCSRegA(reg_t *_ucsra_ptr): Register(_ucsra_ptr) {

}
reg_bit_value_t UCSRegA::get_ucsra_bit(ucsra_bit_number_t _ucsra_bit_number) {
    return get_bit((reg_bit_number_t)_ucsra_bit_number);
}
reg_bit_value_t UCSRegA::set_ucsra_bit(ucsra_bit_number_t _ucsra_bit_number, reg_bit_value_t _val) {
    return set_bit((reg_bit_number_t)_ucsra_bit_number, _val);
}

UCSRegB::UCSRegB(): Register() {

} 
UCSRegB::UCSRegB(reg_t *_ucsrb_ptr): Register(_ucsrb_ptr) {

}
reg_bit_value_t UCSRegB::get_ucsrb_bit(ucsrb_bit_number_t _ucsrb_bit_number) {
    return get_bit((reg_bit_number_t)_ucsrb_bit_number);
}
reg_bit_value_t UCSRegB::set_ucsrb_bit(ucsrb_bit_number_t _ucsrb_bit_number, reg_bit_value_t _val) {
    return set_bit((reg_bit_number_t)_ucsrb_bit_number, _val);
}

UCSRegC::UCSRegC(): Register() {

}
UCSRegC::UCSRegC(reg_t *_ucsrc_ptr): Register(_ucsrc_ptr) {

}
reg_bit_value_t UCSRegC::get_ucsrc_bit(ucsrc_bit_number_t _ucsrc_bit_number) {
    return get_bit((reg_bit_number_t)_ucsrc_bit_number);
}
reg_bit_value_t UCSRegC::set_ucsrc_bit(ucsrc_bit_number_t _ucsrc_bit_number, reg_bit_value_t _val) {
    return set_bit((reg_bit_number_t)_ucsrc_bit_number, _val);
}
