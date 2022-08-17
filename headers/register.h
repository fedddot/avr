#ifndef _REGISTER_H_
#  define _REGISTER_H_

#include <stdio.h>
#include <inttypes.h>

namespace Register {

    enum BitNumber {
        BIT0 = 0,
        BIT1 = 1,
        BIT2 = 2,
        BIT3 = 3,
        BIT4 = 4,
        BIT5 = 5,
        BIT6 = 6,
        BIT7 = 7
    };

    enum BitValue {
        BIT_LOW = 0,
        BIT_HIGH = 1,
        BIT_UNREACHABLE = -1,
        BIT_WRONG_VALUE = -2,
        BIT_READ_ONLY = -3
    };

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
        BitValue set_bit(BitNumber bit, BitValue val);
        BitValue get_bit(BitNumber bit);        

        //  getters/setters
        uint8_t *get_register_ptr();
        void set_register_ptr(uint8_t *_register_ptr);
    };    
}

#endif // _REGISTER_H_