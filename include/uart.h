#ifndef _UART_H_
#define _UART_H_

#include <inttypes.h>

#include "register.h" // Register
#include "uart_spreg.h" // uart_spreg
#include "mcu_spreg.h" // mcu_spreg

#include "sysclk.h" // SysCLK

typedef enum uart_baud_enum {
    UART_BAUD_9600 = 9600,
    UART_BAUD_19200 = 19200,
    UART_BAUD_38400 = 38400,
    UART_BAUD_57600 = 57600,
    UART_BAUD_76800 = 76800,
    UART_BAUD_115200 = 115200,
    UART_BAUD_230400 = 230400,
    UART_BAUD_460800 = 460800,
    UART_BAUD_576000 = 576000,
    UART_BAUD_921600 = 921600
} uart_baud_t;

typedef enum uart_regs_status {
    UART_REGS_OK = 0,
    UART_REGS_UNDEFINED = -1
} uart_regs_status_t;  

class UART {
protected:
    uart_baud_t uart_baud;
    
    UCSRegA ucsra; // Control and status reg A
    UCSRegB ucsrb; // Control and status reg B
    UCSRegC ucsrc; // Control and status reg C
    Register ubrrl;
    Register ubrrh; // Baud rate registers
    Register udr;   // Data register
    
    MCUCReg mcucr; // MCU Control register
    SReg sreg;  // Status register
    
    SysCLK sys_clk;

public:
    // constructors
    UART();
    UART(
        uart_baud_t _uart_baud,
        UCSRegA _ucsra, UCSRegB _ucsrb, UCSRegC _ucsrc, 
        Register _ubrrl, Register _ubrrh, Register _udr, 
        MCUCReg _mcucr, SReg _sreg,
        SysCLK _sys_clk
    );

    // public methods
    //  status
    uart_regs_status_t get_registers_status(void);

    // start/terminate
    

    // getters/setters
    uart_baud_t get_uart_baud(uart_baud_t _uart_baud);                             
    uart_baud_t set_uart_baud(uart_baud_t _uart_baud);

};

#endif // _UART_H_