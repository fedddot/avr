#include "fuses.h" // header file
 
FUSELowReg::FUSELowReg(): Register() {

}
FUSELowReg::FUSELowReg(reg_t *_fuse_low_ptr): Register(_fuse_low_ptr) {

}

fuse_bit_val_t FUSELowReg::get_fuse_bit(fuse_low_bit_number_t _fuse_low_bit_number) {
    return (fuse_bit_val_t)get_bit((reg_bit_number_t)_fuse_low_bit_number);
}
fuse_bit_val_t FUSELowReg::set_fuse_bit(fuse_low_bit_number_t _fuse_low_bit_number, fuse_bit_val_t _val) {
    return (fuse_bit_val_t)set_bit((reg_bit_number_t)_fuse_low_bit_number, (reg_bit_value_t)_val);
}