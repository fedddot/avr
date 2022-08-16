#ifndef _REGISTER_H_
#  define _REGISTER_H_

#include <stdio.h>
#include <inttypes.h>

namespace Register {

    enum ReturningCode {
        SUCCESS = 0,
        ERR_REGISTER_POINTS_TO_NULL = -1,
        ERR_WRONG_VALUE_RECEIVED = -2
    };

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
        NOT_DEFINED = -1,
        LOW = 0,
        HIGH = 1
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
        ReturningCode set_bit(BitNumber bit, BitValue val);
        BitValue get_bit(BitNumber bit);        

        //  getters/setters
        uint8_t *get_register_ptr();
        void set_register_ptr(uint8_t *_register_ptr);
    };    
};

#endif // _REGISTER_H_