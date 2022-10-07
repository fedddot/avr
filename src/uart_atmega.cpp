#include <avr/sfr_defs.h> // registers sfrs
#include <avr/interrupt.h> // cli(), sei()
#include <stdlib.h> // malloc, free

#include "circbuff.h" // CircularBuffer

#include "uart.h" // interface

#ifndef FOSC
#error "FOSC not defined"
#endif

#ifndef LOW_FUSE
#error "LOW_FUSE not defined"
#endif

CircularBuffer *buff_ptr = NULL;

UART::UART() {
	set_uart_mode(UART_MODE_ASYNC_NORMAL_SPEED);
	set_baud_rate(UART_DEFAULT_BAUD_RATE);
	set_parity_mode(UART_PARITY_DISABLED);
	set_stop_bits(UART_ONE_STOP_BIT);
	set_char_size(UART_CHAR_SIZE_8);		
}

UART::UART(uart_mode_t _uart_mode, baud_rate_t _baud_rate, 
        parity_t _parity_mode, stop_bits_t _stop_bits, 
        char_size_t _char_size) {

	set_uart_mode(_uart_mode);
	set_baud_rate(_baud_rate);
	set_parity_mode(_parity_mode);
	set_stop_bits(_stop_bits);
	set_char_size(_char_size);
}

uart_mode_t UART::set_uart_mode(uart_mode_t _uart_mode) {
	uint8_t SREG_bckup = SREG;
	uint8_t mode_number = 0x00;
	uint8_t double_speed = 0x00;
	uint8_t front_side = 0x00;

	cli();

	switch (_uart_mode)
	{
	case UART_MODE_ASYNC_NORMAL_SPEED:
		mode_number = 0x00;
		double_speed = 0x00;
		break;
	case UART_MODE_ASYNC_DOUBLE_SPEED:
		mode_number = 0x00;
		double_speed = 0x01;
		break;
	case UART_MODE_SYNC_RISING:
		mode_number = 0x01;
		front_side = 0x00;
		break;
	case UART_MODE_SYNC_FALLING:
		mode_number = 0x01;
		front_side = 0x01;
		break;
	case UART_MODE_MASTER_SPI:
		mode_number = 0x03;
		break;
	default:
		SREG = SREG_bckup;
		return get_uart_mode();
	}

	if (0 == double_speed) {
		UCSR0A &= ~((uint8_t)1 << U2X0);
	}
	else {
		UCSR0A |= (uint8_t)1 << U2X0;
	}

	if (0 == front_side) {
		UCSR0C &= ~((uint8_t)1 << UCPOL0);
	}
	else {
		UCSR0C |= (uint8_t)1 << UCPOL0;
	}

	UCSR0C &= ~(((uint8_t)1 << UMSEL01) | ((uint8_t)1 << UMSEL00));
	UCSR0C |= mode_number << UMSEL00;

	SREG = SREG_bckup;
	return get_uart_mode();
}

uart_mode_t UART::get_uart_mode(void) {
	uint8_t SREG_bckup = SREG;

	uint8_t mode_number = 0x00;
	uint8_t double_speed = 0x00;
	uint8_t front_side = 0x00;

	uart_mode_t result = UART_MODE_UNDEFINED;

	cli();

	mode_number = (UCSR0C >> UMSEL00) & 0x03;
	double_speed = (UCSR0A >> U2X0) & 0x01;
	front_side = (UCSR0C >> UCPOL0) & 0x01;

	switch (mode_number)
	{
	case 0x00:
		if (0 == double_speed) {
			result = UART_MODE_ASYNC_NORMAL_SPEED;
		}
		else {
			result = UART_MODE_ASYNC_DOUBLE_SPEED;
		}
		break;
	case 0x01:
		if (0 == front_side) {
			result = UART_MODE_SYNC_RISING;
		}
		else {
			result = UART_MODE_SYNC_FALLING;
		}
		break;
	case 0x03:
		result = UART_MODE_MASTER_SPI;
		break;
	default:
		result = UART_MODE_UNDEFINED;
		break;
	}

	SREG = SREG_bckup;
	return result;
}

baud_rate_t UART::set_baud_rate(baud_rate_t _baud_rate) {
	uint8_t SREG_bckup = SREG;
	uint16_t UBRR = 0;
	uint32_t divider = 0;

	cli();

	// TODO: Check if need to divide FOSC by DIVCK8
	switch (get_uart_mode())
	{
	case UART_MODE_ASYNC_NORMAL_SPEED:
		divider = 16;		
		break;
	case UART_MODE_ASYNC_DOUBLE_SPEED:
		divider = 8;
		break;
	case UART_MODE_SYNC_RISING:
		divider = 2;
		break;
	case UART_MODE_SYNC_FALLING:
		divider = 2;
		break;
	default:
		SREG = SREG_bckup;
		return get_baud_rate();
	}

	UBRR = (uint16_t)((uint32_t)FOSC / (uint32_t)_baud_rate / divider);
	if (UBRR > 0) {
		UBRR -= 1;
	}

	UBRR0H = (uint8_t)(UBRR >> 8);
	UBRR0L = (uint8_t)(UBRR);

	SREG = SREG_bckup;
	return get_baud_rate();
}

baud_rate_t UART::get_baud_rate(void) {
	uint16_t UBRR = 0;
	uint8_t SREG_bckup = SREG;
	uint32_t divider = 0;

	baud_rate_t result = 0;

	cli();

	UBRR = ((uint16_t)UBRR0H << 8) | (uint16_t)UBRR0L;

	// TODO: Check if need to divide FOSC by DIVCK8
	switch (get_uart_mode())
	{
	case UART_MODE_ASYNC_NORMAL_SPEED:
		divider = 16;
		break;
	case UART_MODE_ASYNC_DOUBLE_SPEED:
		divider = 8;
		break;
	case UART_MODE_SYNC_RISING:
		divider = 8;
		break;
	case UART_MODE_SYNC_FALLING:
		divider = 8;
		break;

	default:
		return (baud_rate_t)(-1);
	}

	result = (baud_rate_t)((uint32_t)FOSC / divider / ((uint32_t)UBRR + 1));
	SREG = SREG_bckup;
	return result;
}

parity_t UART::set_parity_mode(parity_t _parity_mode) {
	uint8_t SREG_bckup = SREG;
	uint8_t mode_number = 0x00;

	cli();

	switch (_parity_mode)
	{
	case UART_PARITY_DISABLED:
		mode_number = 0x00;
		break;
	case UART_PARITY_EVEN:
		mode_number = 0x02;
		break;
	case UART_PARITY_ODD:
		mode_number = 0x03;
		break;
	default:
		SREG = SREG_bckup;
		return get_parity_mode();
	}

	UCSR0C &= ~(((uint8_t)1 << UPM01) | ((uint8_t)1 << UPM00));
	UCSR0C |= mode_number << UPM00;

	SREG = SREG_bckup;
	return get_parity_mode();
}

parity_t UART::get_parity_mode(void) {
	uint8_t SREG_bckup = SREG;
	uint8_t mode_number = 0x00;

	parity_t result = UART_PARITY_UNDEFINED;

	cli();

	mode_number = (UCSR0C >> UPM00) & 0x03;

	switch (mode_number)
	{
	case 0x00:
		result = UART_PARITY_DISABLED;
		break;
	case 0x02:
		result = UART_PARITY_EVEN;
		break;
	case 0x03:
		result = UART_PARITY_ODD;
		break;
	default:
		result = UART_PARITY_UNDEFINED;
		break;
	}

	SREG = SREG_bckup;
	return result;
}

stop_bits_t UART::set_stop_bits(stop_bits_t _stop_bits) {
	uint8_t SREG_bckup = SREG;

	cli();

	switch (_stop_bits)
	{
	case UART_ONE_STOP_BIT:
		UCSR0C &= ~((uint8_t)1 << USBS0);
		break;
	case UART_TWO_STOP_BITS:
		UCSR0C |= (uint8_t)1 << USBS0;
		break;
	default:
		break;
	}

	SREG = SREG_bckup;
	return get_stop_bits();
}

stop_bits_t UART::get_stop_bits(void) {
	uint8_t SREG_bckup = SREG;
	uint8_t mode_number = 0x00;
	stop_bits_t result = UART_STOP_BITS_UNDEFINED;

	cli();

	mode_number = (UCSR0C >> USBS0) & 0x01;

	switch (mode_number)
	{
	case 0x00:
		result = UART_ONE_STOP_BIT;
		break;
	case 0x01:
		result = UART_TWO_STOP_BITS;
		break;
	default:
		result = UART_STOP_BITS_UNDEFINED;
		break;
	}

	SREG = SREG_bckup;
	return result;
}

char_size_t UART::set_char_size(char_size_t _char_size) {
	uint8_t SREG_bckup = SREG;
	uint8_t mode_number = 0x00;

	cli();

	switch (_char_size)
	{
	case UART_CHAR_SIZE_5:
		mode_number = 0x00;
		break;
	case UART_CHAR_SIZE_6:
		mode_number = 0x01;
		break;
	case UART_CHAR_SIZE_7:
		mode_number = 0x02;
		break;
	case UART_CHAR_SIZE_8:
		mode_number = 0x03;
		break;
	case UART_CHAR_SIZE_9:
		mode_number = 0x07;
		break;
	default:
		SREG = SREG_bckup;
		return get_char_size();
	}

	if (mode_number > 0x03) {
		UCSR0B |= (uint8_t)1 << UCSZ02;
	}
	else {
		UCSR0B &= ~((uint8_t)1 << UCSZ02);
	}

	mode_number &= 0x03;
	UCSR0C |= mode_number << UCSZ00;

	SREG = SREG_bckup;
	return get_char_size();
}

char_size_t UART::get_char_size(void) {
	uint8_t SREG_bckup = SREG;
	uint8_t mode_number = 0x00;

	char_size_t result = UART_CHAR_SIZE_UNDEFINED;

	cli();

	mode_number = (UCSR0C >> UCSZ00) & 0x03;
	if (UCSR0B & ((uint8_t)1 << UCSZ02))
	{
		mode_number |= ((uint8_t)1 << 2);
	}

	switch (mode_number)
	{
	case 0x00:
		result = UART_CHAR_SIZE_5;
		break;
	case 0x01:
		result = UART_CHAR_SIZE_6;
		break;
	case 0x02:
		result = UART_CHAR_SIZE_7;
		break;
	case 0x03:
		result = UART_CHAR_SIZE_8;
		break;
	case 0x07:
		result = UART_CHAR_SIZE_9;
		break;
	default:
		result = UART_CHAR_SIZE_UNDEFINED;
		break;
	}

	SREG = SREG_bckup;
	return result;
}

uart_send_status_t UART::send_bytes(const char *_data, size_t _data_size) {
	uint8_t SREG_bckup = SREG;

	cli();

	UCSR0A &= ~((uint8_t)1 << UDRE0);
	UCSR0B |= (uint8_t)1 << TXEN0;

	while (_data_size) {		
		while (!(UCSR0A & ((uint8_t)1 << UDRE0)))
			;
		UDR0 = *(uint8_t *)_data;

		++_data;
		--_data_size;
	}

	UCSR0B &= ~((uint8_t)1 << TXEN0);
	SREG = SREG_bckup;

	return UART_SEND_SUCCESS;
}

void UART::start_receiver(CircularBuffer *_buff) {
	cli();

	buff_ptr = _buff;
	UCSR0B |= ((uint8_t)1 << RXEN0) | ((uint8_t)1 << RXCIE0);

	sei();
}

void UART::stop_receiver(void) {
	uint8_t SREG_bckup = SREG;

	cli();

	buff_ptr = NULL;
	UCSR0B &= ~(((uint8_t)1 << RXEN0) | ((uint8_t)1 << RXCIE0));

	SREG = SREG_bckup;
}

ISR(USART_RX_vect) {
	uint8_t byte_received = 0;	

	cli();
	byte_received = UDR0;
	buff_ptr->write_byte((char)byte_received);
	sei();
}