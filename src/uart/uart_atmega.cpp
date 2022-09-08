#include <avr/io.h>
#include <inttypes.h> // uint32_t

#include "uart.h" // interface
#include "uart_spec_reg.h" // special registers definitions

#ifndef FOSC
#define FOSC 8000000UL
// #error "Error while preprocessing - FOSC macro undefined"
#endif

//  configuration functions
uart_ret_val_t UART::set_baud_rate(baud_rate_t _baud_rate) {
	
	uint16_t UBRR = 0;
	uart_mode_t _uart_mode = get_uart_mode();
	int K = 1;

	if (BIT_HIGH == UCSR0A.get_bit((reg_bits_t)UCSRA_U2X))
	{
		K = 2;
	}

	switch (_uart_mode)
	{
	case UART_MODE_ASYNC:
		UBRR = (uint32_t)((K * FOSC) / (16 * _baud_rate) - 1);
		break;
	case UART_MODE_SYNC:
		UBRR = (uint32_t)(FOSC / (2 * _baud_rate) - 1);
		break;
	default:
		return UART_FAILURE;
	}

	*(UBRR0H.get_register_ptr()) = (reg_t)(UBRR >> 8) & (reg_t)(-1);
	*(UBRR0L.get_register_ptr()) = (reg_t)(UBRR) & (reg_t)(-1);
	return UART_SUCCESS;
}

uart_ret_val_t UART::set_uart_mode(uart_mode_t _uart_mode) {
	switch (_uart_mode)
	{
	case UART_MODE_ASYNC:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UMSEL0, BIT_LOW);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UMSEL1, BIT_LOW);
		break;
	case UART_MODE_SYNC:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UMSEL0, BIT_HIGH);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UMSEL1, BIT_LOW);
		break;
	case UART_MODE_MASTER_SPI:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UMSEL0, BIT_HIGH);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UMSEL1, BIT_HIGH);
		break;
	default:
		return UART_FAILURE;
	}
	return UART_SUCCESS;
}

uart_ret_val_t UART::set_parity_mode(parity_t _parity_mode) {
	switch (_parity_mode)
	{
	case UART_PARITY_DISABLED:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UPM0, BIT_LOW);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UPM1, BIT_LOW);
		break;
	case UART_PARITY_EVEN:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UPM0, BIT_LOW);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UPM1, BIT_HIGH);
		break;
	case UART_PARITY_ODD:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UPM0, BIT_HIGH);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UPM1, BIT_HIGH);
		break;
	default:
		return UART_FAILURE;
	}
	return UART_SUCCESS;
}

uart_ret_val_t UART::set_stop_bits(stop_bits_t _stop_bits) {
	switch (_stop_bits)
	{
	case UART_ONE_STOP_BIT:
		UCSR0C.set_bit((reg_bits_t)UCSRC_USBS, BIT_LOW);
		break;
	case UART_TWO_STOP_BITS:
		UCSR0C.set_bit((reg_bits_t)UCSRC_USBS, BIT_HIGH);
		break;
	default:
		return UART_FAILURE;
	}
	return UART_SUCCESS;
}

uart_ret_val_t UART::set_char_size(char_size_t _char_size) {
	switch (_char_size)
	{
	case UART_CHAR_SIZE_5:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UCSZ0, BIT_LOW);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UCSZ1, BIT_LOW);
		UCSR0B.set_bit((reg_bits_t)UCSRB_UCSZ2, BIT_LOW);
		break;
	case UART_CHAR_SIZE_6:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UCSZ0, BIT_HIGH);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UCSZ1, BIT_LOW);
		UCSR0B.set_bit((reg_bits_t)UCSRB_UCSZ2, BIT_LOW);
		break;
	case UART_CHAR_SIZE_7:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UCSZ0, BIT_LOW);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UCSZ1, BIT_HIGH);
		UCSR0B.set_bit((reg_bits_t)UCSRB_UCSZ2, BIT_LOW);
		break;
	case UART_CHAR_SIZE_8:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UCSZ0, BIT_HIGH);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UCSZ1, BIT_HIGH);
		UCSR0B.set_bit((reg_bits_t)UCSRB_UCSZ2, BIT_LOW);
		break;
	case UART_CHAR_SIZE_9:
		UCSR0C.set_bit((reg_bits_t)UCSRC_UCSZ0, BIT_HIGH);
		UCSR0C.set_bit((reg_bits_t)UCSRC_UCSZ1, BIT_HIGH);
		UCSR0B.set_bit((reg_bits_t)UCSRB_UCSZ2, BIT_HIGH);
		break;
	default:
		return UART_FAILURE;
	}
	return UART_SUCCESS;
}

uart_ret_val_t UART::sys_update_params(void) {
	if (UART_FAILURE == set_baud_rate(baud_rate))
		return UART_FAILURE;
	if (UART_FAILURE == set_uart_mode(uart_mode))
		return UART_FAILURE;
	if (UART_FAILURE == set_parity_mode(parity_mode))
		return UART_FAILURE;
	if (UART_FAILURE == set_stop_bits(stop_bits))
		return UART_FAILURE;
	if (UART_FAILURE == set_char_size(char_size))
		return UART_FAILURE;
	return UART_SUCCESS;
}

baud_rate_t UART::get_baud_rate(void) {
	uint16_t _ubrrh = (uint16_t)(*(UBRR0H.get_register_ptr()));
	uint16_t _ubrrl = (uint16_t)(*(UBRR0L.get_register_ptr()));
	uint16_t UBRR = (_ubrrh << 8) || _ubrrl;
	uart_mode_t _uart_mode = get_uart_mode();
	int K = 1;
	baud_rate_t baud = 0;

	if (BIT_HIGH == UCSR0A.get_bit((reg_bits_t)UCSRA_U2X))
	{
		K = 2;
	}
	switch (_uart_mode)
	{
	case UART_MODE_ASYNC:
		baud = (baud_rate_t)((K * FOSC) / (16 * (UBRR + 1)));
		break;
	case UART_MODE_SYNC:
		baud = (baud_rate_t)((FOSC) / (8 * (UBRR + 1)));
		break;
	default:
		return UART_FAILURE;
	}
	return baud;
}

uart_mode_t get_uart_mode(void) {
	reg_bit_value_t _umsel0 = UCSR0C.get_bit((reg_bits_t)UCSRC_UMSEL0);
	reg_bit_value_t _umsel1 = UCSR0C.get_bit((reg_bits_t)UCSRC_UMSEL1);
	uint8_t mode_num = 	((uint8_t)(BIT_HIGH == _umsel0)) | \
						((uint8_t)(BIT_HIGH == _umsel1) << 1);
	switch (mode_num)
	{
	case 0x00:		
		return UART_MODE_ASYNC;
	case 0x01:
		return UART_MODE_SYNC;
	case 0x03:
		return UART_MODE_MASTER_SPI;
	default:
		break;
	}
	return UART_MODE_UNDEFINED;
}

parity_t get_parity_mode(void) {
	reg_bit_value_t _upm0 = UCSR0C.get_bit((reg_bits_t)UCSRC_UPM0);
	reg_bit_value_t _upm1 = UCSR0C.get_bit((reg_bits_t)UCSRC_UPM1);
	uint8_t parity_num = ((uint8_t)(BIT_HIGH == _upm0)) | \
						 ((uint8_t)(BIT_HIGH == _upm1) << 1);
	switch (parity_num)
	{
	case 0x00:		
		return UART_PARITY_DISABLED;
	case 0x02:
		return UART_PARITY_EVEN;
	case 0x03:
		return UART_PARITY_ODD;
	default:
		break;
	}
	return UART_PARITY_UNDEFINED;
}

stop_bits_t get_stop_bits(void) {
	switch (UCSR0C.get_bit((reg_bits_t)UCSRC_USBS))
	{
	case BIT_LOW:		
		return UART_ONE_STOP_BIT;
	case BIT_HIGH:
		return UART_TWO_STOP_BITS;
	default:
		break;
	}
	return UART_STOP_BITS_UNDEFINED;
}

char_size_t get_char_size(void) {
	reg_bit_value_t _ucsz0 = UCSR0C.get_bit((reg_bits_t)UCSRC_UCSZ0);
	reg_bit_value_t _ucsz1 = UCSR0C.get_bit((reg_bits_t)UCSRC_UCSZ1);
	reg_bit_value_t _ucsz2 = UCSR0B.get_bit((reg_bits_t)UCSRB_UCSZ2);
	uint8_t char_size_num = ((uint8_t)(BIT_HIGH == _ucsz0)) | \
						 	((uint8_t)(BIT_HIGH == _ucsz1) << 1) | \
							((uint8_t)(BIT_HIGH == _ucsz2) << 2);
	switch (char_size_num)
	{
	case 0x00:		
		return UART_CHAR_SIZE_5;
	case 0x01:
		return UART_CHAR_SIZE_6;
	case 0x02:
		return UART_CHAR_SIZE_7;
	case 0x03:
		return UART_CHAR_SIZE_8;
	case 0x07:
		return UART_CHAR_SIZE_9;
	default:
		break;
	}
	return UART_CHAR_SIZE_UNDEFINED;

}

// 	constructors

// 	UART::UART();

// 	TODO: Sophisticated getters/setters
UART::UART(baud_rate_t _baud_rate, parity_t _parity_mode, uart_mode_t _uart_mode,
        stop_bits_t _stop_bits, char_size_t _char_size) {
	baud_rate = _baud_rate;
	parity_mode = _parity_mode;
	uart_mode = _uart_mode;
	stop_bits = _stop_bits;
	char_size = _char_size;
}

// TODO: Implementation
uart_ret_val_t UART::send_char(uart_char_t _ch) {
	(void)(_ch);
	return UART_FAILURE;
}

// TODO: Implementation
uart_char_t UART::receive_char(void) {
	return 0x00;
}