#include <stddef.h> // NULL

#include "register.h"

// constructors
Register::Register() {
    // Default constructor
}

Register::Register(reg_t *_register_ptr) {
    set_register_ptr(_register_ptr);
}

// public methods
//  bitwise operations
reg_bit_value_t Register::set_bit(reg_bit_number_t _bit, reg_bit_value_t _val) {
    if (register_ptr == NULL) 
        return BIT_UNDEFINED;
    
    switch (_val) {
        case BIT_HIGH:
            *register_ptr |= (1 << _bit);
            return BIT_HIGH;
        case BIT_LOW:
            *register_ptr &= ~(1 << _bit);
            return BIT_LOW;
        default:
            return BIT_UNDEFINED;
    }   
}

reg_bit_value_t Register::get_bit(reg_bit_number_t _bit) {
    if (register_ptr == NULL) 
        return BIT_UNDEFINED;
    if ((1 << _bit) & *register_ptr) 
        return BIT_HIGH;
    else 
        return BIT_LOW; 
}

//  getters/setters
reg_t *Register::get_register_ptr() {
    return register_ptr;
}

void Register::set_register_ptr(reg_t *_register_ptr) {
    register_ptr = _register_ptr;
}