#include <stdlib.h> // malloc, free

#include "circbuff.h" // interface

static char *move_ptr_fwd(char *base, size_t base_len, char *ptr);

CircularBuffer::CircularBuffer(size_t _capacity) {
    buffer_ptr = (char *)malloc(sizeof(char) * _capacity);
    capacity = _capacity;
    read_ptr = NULL;
    write_ptr = buffer_ptr;
}

CircularBuffer::~CircularBuffer() {
    if (NULL != buffer_ptr) {
        free(buffer_ptr);
        buffer_ptr = NULL;
    }
}

void CircularBuffer::flush_buff(void) {
    read_ptr = NULL;
    write_ptr = buffer_ptr;
}

size_t CircularBuffer::write_bytes(const char *src, size_t nbytes) {
    size_t nbytes_bckup = nbytes;

    if ((NULL == src) || (1 > nbytes)) {
        return 0;
    }

    if (NULL == read_ptr) {
        *write_ptr = *src;
        read_ptr = (const char *)write_ptr;
        write_ptr = move_ptr_fwd(buffer_ptr, capacity, write_ptr);
        ++src;
        --nbytes;
    }

    while (nbytes) {
        *write_ptr = *src;
        write_ptr = move_ptr_fwd(buffer_ptr, capacity, write_ptr);
        ++src;
        --nbytes;
        if (write_ptr == read_ptr) {
            read_ptr = (const char *)move_ptr_fwd(buffer_ptr, capacity, (char *)read_ptr);
        }
    }

    return nbytes_bckup;
}

size_t CircularBuffer::read_bytes(char *dest, size_t nbytes) {
    size_t nbytes_bckup = nbytes;

    if ((NULL == read_ptr) || (NULL == dest) || (1 > nbytes)) {
        return 0;
    }

    while (nbytes) {
        *dest = *read_ptr;
        read_ptr = (const char *)move_ptr_fwd(buffer_ptr, capacity, (char *)read_ptr);
        ++dest;
        --nbytes;
        if (read_ptr == write_ptr) {
            read_ptr = NULL;
            write_ptr = buffer_ptr;
            break;
        }
    }
    return nbytes_bckup - nbytes;
}

size_t CircularBuffer::get_capacity(void) {
    return capacity;
}

size_t CircularBuffer::get_size(void) {
    const char *read_runner = NULL;
    size_t count = 0;

    if (NULL == read_ptr) {
        return 0;
    }

    read_runner = read_ptr;
    while (read_runner != write_ptr) {
        read_runner = (const char *)move_ptr_fwd(
            buffer_ptr, 
            capacity, 
            (char *)read_runner
        );
        ++count;
    }
    return count;
}



static char *move_ptr_fwd(char *base, size_t base_len, char *ptr) {
    ++ptr;
    if (base + base_len <= ptr) {
        return base;
    }
    return ptr;
}