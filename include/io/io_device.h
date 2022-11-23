#ifndef __IO_DEV_H__
#define __IO_DEV_H__

#include <stdlib.h>

class IODevice {
public:

    /// @brief write num elements into device from src_ptr
    /// @param src_ptr pointer to the source
    /// @param num number of elements to write
    /// @return number of elements successfully written
    virtual size_t write(const void *src_ptr, size_t num) = 0;

    /// @brief read num elements from device into dest_ptr
    /// @param dest_ptr pointer to the destination
    /// @param num number of elements to read
    /// @return number of elements successfully read
    virtual size_t read(void *dest_ptr, size_t num) = 0;
};

#endif // __IO_DEV_H__