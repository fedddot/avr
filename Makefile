# Variables
INCLUDE = ./include
SRC = ./src
MDL = ./modules

# AVR settings
AVR_CC = avr-g++
AVR_MCU = atmega328p
AVR_LFUSE = 0xEE
AVR_HFUSE = 0xD9
AVR_EFUSE = 0xFF
AVR_FOSC = 16000000UL
AVR_PRM = -mmcu=$(AVR_MCU) -DFOSC=$(AVR_FOSC) -DF_CPU=$(AVR_FOSC) -DLOW_FUSE=$(AVR_LFUSE) -ansi -pedantic-errors -Wall -Wextra -Wcpp

uart_atmega.o : $(SRC)/uart_atmega.cpp $(INCLUDE)/uart.h
	$(AVR_CC) $(AVR_PRM) -I$(INCLUDE) -c $< -o $@

circbuff.o : $(SRC)/circbuff.cpp $(INCLUDE)/circbuff.h
	$(AVR_CC) $(AVR_PRM) -I$(INCLUDE) -c $< -o $@

firmware.o : $(MDL)/firmware.cpp $(INCLUDE)/uart.h $(INCLUDE)/circbuff.h
	$(AVR_CC) $(AVR_PRM) -I$(INCLUDE) -c $< -o $@

firmware.hex : firmware.o uart_atmega.o circbuff.o
	$(AVR_CC) $(AVR_PRM) -I$(INCLUDE) $^ -o $@

circbuff_test.out : $(MDL)/circbuff_test.cpp $(SRC)/circbuff.cpp $(INCLUDE)/circbuff.h
	g++ -ansi -pedantic-errors -Wall -Wextra -g -I$(INCLUDE) $(MDL)/circbuff_test.cpp $(SRC)/circbuff.cpp -o $@

.PHONY: clean
clean : 
	rm *.hex *.o *.out

PORT_PATH = /dev/bus/usb/001/012
PART_NUMBER = m328p
FUSES = -U lfuse:w:$(AVR_LFUSE):m -U hfuse:w:$(AVR_HFUSE):m -U efuse:w:$(AVR_EFUSE):m
FIRMWARE_FILE = -U flash:w:firmware.hex

.PHONY: upload
upload : 
	avrdude -c usbasp -P $(PORT_PATH) -p $(PART_NUMBER) -F -v $(FUSES) $(FIRMWARE_FILE)
