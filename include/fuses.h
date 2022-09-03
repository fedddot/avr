#ifndef _FUSES_H_
#define _FUSES_H_

#include "register.h" /* Register */

typedef enum fuse_bit_val {
    FUSE_BIT_VAL_PROGRAMMED = BIT_LOW,
    FUSE_BIT_VAL_UNPROGRAMMED = BIT_HIGH
} fuse_bit_val_t;

typedef enum fuse_feature_status {
    FUSE_FEATURE_DISABLED = 0,
    FUSE_FEATURE_ENABLED = 1
} fuse_feature_status_t;

typedef enum fuse_low_bit_number {
    FUSE_LOW_CKSEL0 = BIT0,
    FUSE_LOW_CKSEL1 = BIT1,
    FUSE_LOW_CKSEL2 = BIT2,
    FUSE_LOW_CKSEL3 = BIT3,
    FUSE_LOW_SUT0 = BIT4,
    FUSE_LOW_SUT1 = BIT5,
    FUSE_LOW_CKOUT = BIT6,
    FUSE_LOW_CKDIV8 = BIT7
} fuse_low_bit_number_t;

class FUSELowReg: Register {
public:
    FUSELowReg();
    FUSELowReg(reg_t *_fuse_low_ptr);
    fuse_bit_val_t get_fuse_bit(fuse_low_bit_number_t _fuse_low_bit_number);
    fuse_bit_val_t set_fuse_bit(fuse_low_bit_number_t _fuse_low_bit_number, fuse_bit_val_t _val);
};

#endif // _FUSES_H_
