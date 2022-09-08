#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <stdio.h> // NULL

// class template declaration

typedef unsigned char reg_t;
typedef enum reg_bit_value reg_bit_value_t;
typedef enum reg_bits reg_bits_t;

class Register {
protected:
    // protected fields
    reg_t *register_ptr;
public:
    // constructors
    Register();
    Register(reg_t *_register_ptr);

    // public methods
    //  bitwise operations
    reg_bit_value_t set_bit(reg_bits_t _bit, reg_bit_value_t _val);
    reg_bit_value_t get_bit(reg_bits_t _bit);        

    //  getters/setters
    reg_t *get_register_ptr();
    void set_register_ptr(reg_t *_register_ptr);
};

// enums implementations

enum reg_bit_value {
    BIT_LOW = 0,
    BIT_HIGH = 1,
    BIT_UNDEFINED = -1
};

enum reg_bits {
    BIT_0 = 0,
    BIT_1 = 1,
    BIT_2 = 2,
    BIT_3 = 3,
    BIT_4 = 4,
    BIT_5 = 5,
    BIT_6 = 6,
    BIT_7 = 7
};

#endif // _REGISTER_H_