#include <stdlib.h> // malloc, free

#include "circbuff.h" // interface

int CircBuff::is_empty(void) {
    return NULL == read_ptr;
}

char *CircBuff::next_ptr(const char *ptr) {
    ++ptr;
    if (buffer_ptr + capacity <= ptr) {
        return buffer_ptr;
    }
    return (char *)ptr;
}

CircBuff::CircBuff(size_t _capacity) {
    buffer_ptr = (char *)malloc(sizeof(char) * _capacity);
    capacity = _capacity;
    read_ptr = NULL;
    write_ptr = buffer_ptr;
}

CircBuff::~CircBuff() {
    if (NULL != buffer_ptr) {
        free(buffer_ptr);
        buffer_ptr = NULL;
    }
}

void CircBuff::flush(void) {
    read_ptr = NULL;
    write_ptr = buffer_ptr;
}

void CircBuff::write_byte(char _byte) {
    *write_ptr = _byte;
    if (is_empty()) {
        read_ptr = (const char *)write_ptr;
    } else if (read_ptr == write_ptr) {
        read_ptr = (const char *)next_ptr(read_ptr);
    }
    write_ptr = next_ptr((const char *)write_ptr);
}

int CircBuff::read_byte(char *_byte_ptr) {
    if (is_empty() || (NULL == _byte_ptr)) {
        return -1;
    }
    *_byte_ptr = *read_ptr;
    read_ptr = (const char *)next_ptr(read_ptr);
    if (read_ptr == write_ptr) {
        read_ptr = NULL;
    }
    return 0;
}

size_t CircBuff::write_bytes(const char *src, size_t nbytes) {
    const char *src_end = NULL;

    if (NULL == src) {
        return 0;
    }

    src_end = src + nbytes;
    
    while (src_end > src) {
        write_byte(*src);
        ++src;
    }

    return nbytes;
}

size_t CircBuff::read_bytes(char *dest, size_t nbytes) {
    char *dest_start = NULL;
    char *dest_end = NULL;

    if (NULL == dest) {
        return 0;
    }

    dest_start = dest;
    dest_end = dest + nbytes;

    while (dest_end > dest)
    {
        if (0 != read_byte(dest)) {
            break;
        }
        ++dest;
    }

    return (size_t)(dest - dest_start);
}

size_t CircBuff::get_capacity(void) {
    return capacity;
}

size_t CircBuff::get_size(void) {
    if (is_empty()) {
        return 0;
    }

    if (write_ptr > read_ptr) {
        return (size_t)(write_ptr - read_ptr);
    } else if (write_ptr < read_ptr) {
        return capacity - (size_t)(read_ptr - write_ptr);
    } else {
        return capacity;
    }
}

