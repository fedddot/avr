#ifndef _CIRCBUFF_H_
#define _CIRCBUFF_H_

#include <stddef.h> // size_t

class CircBuff {
    char *buffer_ptr;
    size_t capacity;
    const char *read_ptr;
    char *write_ptr;

    int is_empty(void);
    char *next_ptr(const char *ptr);
public:
    CircBuff(size_t _capacity);

    ~CircBuff();

    void flush(void);

    void write_byte(char _byte);
    int read_byte(char *_byte_ptr);
    
    size_t write_bytes(const char *src, size_t nbytes);
    size_t read_bytes(char *dest, size_t nbytes);

    size_t get_capacity(void);
    size_t get_size(void);
};

#endif // _CIRCBUFF_H_