#include "register.h"

// constructors
Register::Register::Register() {
    // Default constructor
};

Register::Register::Register(uint8_t *_register_ptr) {
    set_register_ptr(_register_ptr);
};

// public methods
//  bitwise operations
Register::ReturningCode Register::Register::set_bit(BitNumber bit, BitValue val) {
    if (register_ptr == NULL) {
        return ERR_REGISTER_POINTS_TO_NULL;
    }
    switch (val)
    {
    case HIGH:
        *register_ptr = (uint8_t)(*register_ptr | (1 << bit));
        return SUCCESS;
    case LOW:
        *register_ptr = (uint8_t)(*register_ptr & ~(1 << bit));
        return SUCCESS;
    default:
        return ERR_WRONG_VALUE_RECEIVED;
    }   
};

Register::BitValue Register::Register::get_bit(BitNumber bit) {
    if (register_ptr == NULL) {
        return NOT_DEFINED;
    }
    if ((uint8_t)(1 << bit) & *register_ptr) {
        return HIGH;
    } else {
        return LOW;
    }  
};

//  getters/setters
uint8_t *Register::Register::get_register_ptr() {
    return register_ptr;
};
void Register::Register::set_register_ptr(uint8_t *_register_ptr) {
    register_ptr = _register_ptr;
};