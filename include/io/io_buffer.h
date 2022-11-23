#ifndef __IO_BUFFER_H__
#define __IO_BUFFER_H__

#include <stdlib.h> // size_t

class IOBuffer {
public:

    /// @brief function writes num elements from src_ptr into the buffer memory
    /// @param src_ptr pointer to the source
    /// @param num number of elements
    /// @return number of successfully written elements
    virtual size_t write(const void *src_ptr, size_t num) = 0;

    /// @brief function reads num elements from the buffer memory into dest_ptr
    /// @param dest_ptr pointer to the destination
    /// @param num number of elements
    /// @return number of successfully read elements
    virtual size_t read(void *dest_ptr, size_t num) = 0;

    /// @brief function flushes all the data stored in the buffer
    void flush(void);
};

#endif // __IO_BUFFER_H__