#include <avr/io.h>
#include <util/twi.h>

#include "io/twi_master.h"

#define TW_SCL_PIN			PORTC5
#define TW_SDA_PIN			PORTC4

#define TW_SLA_W(ADDR)		((ADDR << 1) | TW_WRITE)
#define TW_SLA_R(ADDR)		((ADDR << 1) | TW_READ)
#define TW_READ_ACK			1
#define TW_READ_NACK		0

/* private functions declarations */

static status_t tw_start(void);
static void tw_stop(void);
static status_t tw_write_sla(unsigned char sla);
static status_t tw_write(char data);
static char tw_read(int read_ack);

/* public functions implementations */

void twi_init(twi_freq_mode_t twi_freq_mode, int pullup_en)
{
	DDRC  |= (1 << TW_SDA_PIN) | (1 << TW_SCL_PIN);
	
	if (pullup_en)
	{
		PORTC |= (1 << TW_SDA_PIN) | (1 << TW_SCL_PIN);
	}
	else
	{
		PORTC &= ~((1 << TW_SDA_PIN) | (1 << TW_SCL_PIN));
	}

	DDRC  &= ~((1 << TW_SDA_PIN) | (1 << TW_SCL_PIN));
	
	/* TODO: make it more generic */
	switch (twi_freq_mode)
	{
	case TW_FREQ_100K:
		/* Set bit rate register 72 and prescaler to 1 resulting in
		SCL_freq = 16MHz/(16 + 2*72*1) = 100KHz	*/
		TWBR = 72;
		break;
		
	case TW_FREQ_250K:
		/* Set bit rate register 24 and prescaler to 1 resulting in
		SCL_freq = 16MHz/(16 + 2*24*1) = 250KHz	*/
		TWBR = 24;
		break;
		
	case TW_FREQ_400K:
		/* Set bit rate register 12 and prescaler to 1 resulting in
		SCL_freq = 16MHz/(16 + 2*12*1) = 400KHz	*/
		TWBR = 12;
		break;
		
	default: 
		break;
	}
}

status_t twi_master_transmit(unsigned char slave_addr, const char *src_ptr, size_t len, int repeat_start)
{
	const char *src_end_ptr = NULL;
	if (FAILURE == tw_start())
	{
		return FAILURE;
	}
	
	if (FAILURE == tw_write_sla(TW_SLA_W(slave_addr)))
	{
		return FAILURE;
	}
	
	src_end_ptr = src_ptr + len;
	while (src_end_ptr > src_ptr)
	{
		if (FAILURE == tw_write(*src_ptr))
		{
			return FAILURE;
		}
		++src_ptr;
	}
	
	if (!repeat_start)
	{
		tw_stop();
	}
	
	return SUCCESS;
}

status_t twi_master_receive(unsigned char slave_addr, char *dest_ptr, char len)
{
	char *dest_end_ptr = NULL;

	if (FAILURE == tw_start())
	{
		return FAILURE;
	}
	
	if (FAILURE == tw_write_sla(TW_SLA_R(slave_addr)))
	{
		return FAILURE;
	}
	
	dest_end_ptr = dest_ptr + len;
	while (dest_end_ptr - 1 > dest_ptr)
	{
		*dest_ptr = tw_read(TW_READ_ACK);
		++dest_ptr;
	}
	*dest_ptr = tw_read(TW_READ_NACK);

	tw_stop();
	
	return SUCCESS;
}

/* statuc functions implementations */

static status_t tw_start(void)
{
	TWCR =  (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	while (!(TWCR & (1 << TWINT)));
	if (TW_STATUS != TW_START && TW_STATUS != TW_REP_START)
	{
		return FAILURE;
	}
	return SUCCESS;
}

static void tw_stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

static status_t tw_write_sla(unsigned char sla)
{
	TWDR = sla;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	if (TW_STATUS != TW_MT_SLA_ACK && TW_STATUS != TW_MR_SLA_ACK)
	{
		return TW_STATUS;
	}
	return SUCCESS;
}

static status_t tw_write(char data)
{
	TWDR = (unsigned char)data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	if (TW_STATUS != TW_MT_DATA_ACK)
	{
		return TW_STATUS;
	}
	return SUCCESS;
}

static char tw_read(int read_ack)
{
	if (read_ack)
	{
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		while (!(TWCR & (1 << TWINT)));
		if (TW_STATUS != TW_MR_DATA_ACK)
		{
			return TW_STATUS;
		}
	}
	else
	{
		TWCR = (1 << TWINT) | (1 << TWEN);
		while (!(TWCR & (1 << TWINT)));
		if (TW_STATUS != TW_MR_DATA_NACK)
		{
			return TW_STATUS;
		}
	}
	return (char)TWDR;
}
