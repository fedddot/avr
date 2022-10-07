#ifndef _CIRCBUFF_H_
#define _CIRCBUFF_H_

#include <stddef.h> // size_t

class CircularBuffer {
    char *buffer_ptr;
    size_t capacity;
    const char *read_ptr;
    char *write_ptr;
public:
    CircularBuffer(size_t _capacity);

    ~CircularBuffer();

    void flush_buff(void);
    
    size_t write_bytes(const char *src, size_t nbytes);
    size_t read_bytes(char *dest, size_t nbytes);

    size_t get_capacity(void);
    size_t get_size(void);
};

#endif // _CIRCBUFF_H_