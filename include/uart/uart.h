#ifndef _UART_H_
#define _UART_H_

#include <inttypes.h> // int16_t

#include "sysclk.h" // clk_freq_t

typedef int16_t baud_rate_t;
typedef int16_t uart_char_t;

typedef enum uart_mode_enum uart_mode_t;
typedef enum parity_enum parity_t;
typedef enum stop_bits_enum stop_bits_t;
typedef enum char_size_enum char_size_t;

typedef enum uart_ret_val_enum uart_ret_val_t;

class UART {
private:
    baud_rate_t baud_rate;
    parity_t parity_mode;
    uart_mode_t uart_mode;
    stop_bits_t stop_bits;
    char_size_t char_size;


    //  configuration methods:
    uart_ret_val_t set_baud_rate(baud_rate_t _baud_rate);
    uart_ret_val_t set_uart_mode(uart_mode_t _uart_mode);
    uart_ret_val_t set_parity_mode(parity_t _parity_mode);
    uart_ret_val_t set_stop_bits(stop_bits_t _stop_bits);
    uart_ret_val_t set_char_size(char_size_t _char_size);
    uart_ret_val_t sys_update_params(void);

    baud_rate_t get_baud_rate(void);
    uart_mode_t get_uart_mode(void);
    parity_t get_parity_mode(void);
    stop_bits_t get_stop_bits(void);
    char_size_t get_char_size(void);


public:
    // constructors
    // UART();
    UART(baud_rate_t _baud_rate, parity_t _parity_mode, uart_mode_t _uart_mode,
         stop_bits_t stop_bits, char_size_t _char_size);
    
    uart_ret_val_t send_char(uart_char_t _ch);
    uart_char_t receive_char(void);
};

enum uart_mode_enum {
    UART_MODE_ASYNC = 0,
    UART_MODE_SYNC = 1,
    UART_MODE_MASTER_SPI = 3,
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

enum uart_ret_val_enum {
    UART_SUCCESS = 0,
    UART_FAILURE = 1
};

#endif // _UART_H_