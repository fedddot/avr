#include "register.h"


// constructors
Kernel::Register::Register() {
    // Default constructor
};

Kernel::Register::Register(uint8_t *_register_ptr) {
    set_register_ptr(_register_ptr);
};

// public methods
void Kernel::Register::set_bit(KernelTypes::bitnum_t bit, KernelTypes::bitval_t val) {
    switch (val)
    {
    case KernelTypes::high:
        *register_ptr = (uint8_t)(*register_ptr | (1 << bit));
    case KernelTypes::low:
        *register_ptr = (uint8_t)(*register_ptr & ~(1 << bit));
    }   
};

KernelTypes::bitval_t Kernel::Register::get_bit(KernelTypes::bitnum_t bit) {
    if ((uint8_t)(1 << bit) & *register_ptr) {
        return KernelTypes::high;
    } else {
        return KernelTypes::low;
    }  
};

//  getters/setters
uint8_t *Kernel::Register::get_register_ptr() {
    return register_ptr;
};
void Kernel::Register::set_register_ptr(uint8_t *_register_ptr) {
    register_ptr = _register_ptr;
};