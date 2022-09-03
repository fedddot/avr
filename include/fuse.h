#ifndef _FUSE_H_
#define _FUSE_H_

#include <inttypes.h> /* uint8_t */

typedef uint8_t fuse_t;

typedef enum fuse_bit_val {
    PROGRAMMED = 0,
    UNPROGRAMMED = 1
} fuse_bit_val_t;

typedef enum fuse_feature_status {
    FUSE_FEATURE_DISABLED = 0,
    FUSE_FEATURE_ENABLED = 1
} fuse_feature_status_t;

class FUSE {
protected:
    fuse_t fuse;
public:
    // constructors
    FUSE();
    FUSE(fuse_t _fuse);

    fuse_t get_fuse(void);
    void set_fuse(fuse_t _fuse);
};

#endif // _FUSE_H_