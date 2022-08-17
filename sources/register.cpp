#include "register.h"

// constructors
Register::Register::Register() {
    // Default constructor
}

Register::Register::Register(uint8_t *_register_ptr) {
    set_register_ptr(_register_ptr);
}

// public methods
//  bitwise operations
Register::BitValue Register::Register::set_bit(BitNumber bit, BitValue val) {
    if (register_ptr == NULL) 
        return BIT_UNREACHABLE;
    
    switch (val) {
        case BIT_HIGH:
            *register_ptr = (uint8_t)(*register_ptr | (1 << bit));
            return BIT_HIGH;
        case BIT_LOW:
            *register_ptr = (uint8_t)(*register_ptr & ~(1 << bit));
            return BIT_LOW;
        default:
            return BIT_WRONG_VALUE;
    }   
}

Register::BitValue Register::Register::get_bit(BitNumber bit) {
    if (register_ptr == NULL) 
        return BIT_UNREACHABLE;
    if ((uint8_t)(1 << bit) & *register_ptr) 
        return BIT_HIGH;
    else 
        return BIT_LOW; 
}

//  getters/setters
uint8_t *Register::Register::get_register_ptr() {
    return register_ptr;
}

void Register::Register::set_register_ptr(uint8_t *_register_ptr) {
    register_ptr = _register_ptr;
}