#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <stdio.h>
#include <inttypes.h>

typedef enum reg_bit_number {
    BIT0 = 0,
    BIT1 = 1,
    BIT2 = 2,
    BIT3 = 3,
    BIT4 = 4,
    BIT5 = 5,
    BIT6 = 6,
    BIT7 = 7
} reg_bit_number_t;

typedef enum reg_bit_value {
    BIT_LOW = 0,
    BIT_HIGH = 1,
    BIT_UNDEFINED = -1
} reg_bit_value_t;

typedef volatile uint8_t reg_t;

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
    reg_bit_value_t set_bit(reg_bit_number_t _bit, reg_bit_value_t _val);
    reg_bit_value_t get_bit(reg_bit_number_t _bit);        

    //  getters/setters
    reg_t *get_register_ptr();
    void set_register_ptr(reg_t *_register_ptr);
};

#endif // _REGISTER_H_