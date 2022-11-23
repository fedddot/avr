#ifndef _UART_H_
#define _UART_H_

#include <inttypes.h> // uint32_t, uint8_t
#include <stddef.h> // size_t

#include "data/circbuff.h" // CircularBuffer

#define UART_DEFAULT_BAUD_RATE 9600
#define UART_DEFAULT_BUFFER_SIZE 0

typedef uint32_t baud_rate_t;

enum uart_mode_enum {
    UART_MODE_ASYNC_NORMAL_SPEED = 0,
    UART_MODE_ASYNC_DOUBLE_SPEED = 1,
    UART_MODE_SYNC_RISING = 2,
    UART_MODE_SYNC_FALLING = 3,
    UART_MODE_MASTER_SPI = 4,
    UART_MODE_UNDEFINED = -1
};

enum parity_enum {
    UART_PARITY_DISABLED = 0,
    UART_PARITY_EVEN = 2,
    UART_PARITY_ODD = 3,
    UART_PARITY_UNDEFINED = -1
};

enum stop_bits_enum {
    UART_ONE_STOP_BIT = 0,
    UART_TWO_STOP_BITS = 1,
    UART_STOP_BITS_UNDEFINED = -1
};

enum char_size_enum {
    UART_CHAR_SIZE_5 = 0,
    UART_CHAR_SIZE_6 = 1,
    UART_CHAR_SIZE_7 = 2,
    UART_CHAR_SIZE_8 = 3,
    UART_CHAR_SIZE_9 = 7,
    UART_CHAR_SIZE_UNDEFINED = -1
};

enum uart_send_status_enum {
    UART_SEND_SUCCESS = 0,
    UART_SEND_FAILURE = -1
};

enum uart_receiver_status_enum {
    UART_RECEIVER_SUCCESS = 0,
    UART_RECEIVER_FAILURE = -1
};

typedef enum uart_mode_enum uart_mode_t;
typedef enum parity_enum parity_t;
typedef enum stop_bits_enum stop_bits_t;
typedef enum char_size_enum char_size_t;
typedef enum uart_send_status_enum uart_send_status_t;
typedef enum uart_receiver_status_enum uart_receiver_status_t;

class UART {
private:
public:
    // constructors

    UART();
    UART(uart_mode_t _uart_mode, baud_rate_t _baud_rate, 
        parity_t _parity_mode, stop_bits_t _stop_bits, 
        char_size_t _char_size);

    uart_mode_t set_uart_mode(uart_mode_t _uart_mode);
    uart_mode_t get_uart_mode(void);

    baud_rate_t set_baud_rate(baud_rate_t _baud_rate);
    baud_rate_t get_baud_rate(void);

    parity_t set_parity_mode(parity_t _parity_mode);
    parity_t get_parity_mode(void);

    stop_bits_t set_stop_bits(stop_bits_t _stop_bits);
    stop_bits_t get_stop_bits(void);

    char_size_t set_char_size(char_size_t _char_size);
    char_size_t get_char_size(void);

    uart_send_status_t send_bytes(const char *src, size_t nbytes);
    
    uart_receiver_status_t start_receiver(size_t buff_capacity);
    void stop_receiver(void);

    size_t get_buffer_capacity(void);
    size_t get_buffer_size(void);
    size_t read_buffer(char *dest, size_t nbytes);
    void flush_buffer(void);
};


#endif // _UART_H_