#ifndef __TWI_MASTER_H__
#define __TWI_MASTER_H__

#include <stdlib.h>

typedef enum status_enum
{
	SUCCESS,
	FAILURE
} status_t;

/* TODO: get rid of it - make a normal freq evaluation */
typedef enum {
	TW_FREQ_100K,
	TW_FREQ_250K,
	TW_FREQ_400K
} twi_freq_mode_t;

void twi_init(twi_freq_mode_t twi_freq_mode, int pullup_en);

status_t twi_master_transmit(unsigned char slave_addr, const char *src_ptr, size_t len, int repeat_start);

status_t twi_master_receive(unsigned char slave_addr, char *dest_ptr, char len);

#endif /* __TWI_MASTER_H__ */