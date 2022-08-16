#ifndef _REGISTER_H_
#  define _REGISTER_H_

#include <stdio.h>
#include <inttypes.h>
#include "kernel_types.h"

namespace Kernel {

    class Register {
    protected:
        // protected fields
        uint8_t *register_ptr = NULL;
    public:
        // constructors
        Register();
        Register(uint8_t *_register_ptr);

        // public methods
        //  bitwise operations
        void set_bit(KernelTypes::bitnum_t bit, KernelTypes::bitval_t val);
        KernelTypes::bitval_t get_bit(KernelTypes::bitnum_t bit);        

        //  getters/setters
        uint8_t *get_register_ptr();
        void set_register_ptr(uint8_t *_register_ptr);
    };    
};

#endif // _REGISTER_H_