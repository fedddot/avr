# Variables
INCLUDE = ./include
SRC = ./src
MDL = ./modules

# AVR settings
AVR_CC = avr-gcc
AVR_MCU = atmega328p
AVR_LFUSE = 0xEE
AVR_HFUSE = 0xD9
AVR_EFUSE = 0xFF
AVR_F_CPU = 16000000UL
AVR_PRM = -mmcu=$(AVR_MCU) -DF_CPU=$(AVR_F_CPU) -ansi -pedantic-errors -Wall -Wextra -Wcpp -g

uart_atmega.o : $(SRC)/io/uart_atmega.cpp $(INCLUDE)/io/uart.h
	$(AVR_CC) $(AVR_PRM) -I$(INCLUDE) -c $< -o $@

twi_master.o : $(SRC)/io/twi_master.c $(INCLUDE)/io/twi_master.h
	$(AVR_CC) $(AVR_PRM) -I$(INCLUDE) -c $< -o $@

circbuff.o : $(SRC)/data/circbuff.cpp $(INCLUDE)/data/circbuff.h
	$(AVR_CC) $(AVR_PRM) -I$(INCLUDE) -c $< -o $@

firmware.o : $(MDL)/firmware.cpp $(INCLUDE)/io/uart.h $(INCLUDE)/data/circbuff.h
	$(AVR_CC) $(AVR_PRM) -I$(INCLUDE) -c $< -o $@

firmware.elf : firmware.o uart_atmega.o circbuff.o
	$(AVR_CC) $(AVR_PRM) -I$(INCLUDE) $^ -o $@

dbg_% : %.elf
	avr-gdb -exec=$< -directory=$(SRC) -tty=tty $<

sim_% : %.elf
	simavr -f $(AVR_F_CPU) -m $(AVR_MCU) -g -ff $<


.PHONY: clean
clean : 
	rm -f *.hex *.elf *.o *.out

PORT_PATH = /dev/bus/usb/001/012
PART_NUMBER = m328p
FUSES = -U lfuse:w:$(AVR_LFUSE):m -U hfuse:w:$(AVR_HFUSE):m -U efuse:w:$(AVR_EFUSE):m
FIRMWARE_FILE = -U flash:w:firmware.hex

.PHONY: upload
upload : 
	avrdude -c usbasp -P $(PORT_PATH) -p $(PART_NUMBER) -F -v $(FUSES) $(FIRMWARE_FILE)
