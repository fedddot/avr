# Variables
INCLUDE = ./include
SRC = ./src
MDL = ./modules

# LINUX settings
CC = g++
CFLAGS = -std=gnu++17 -pedantic-errors -Wall -Wextra -Wcpp -I ${INCLUDE}

# regtest
# regtest : regtest.o register.o
# 	$(CC) $(CFLAGS) -o resgtest regtest.o register.o

regtest : $(MDL)/regtest.cpp
	$(CC) $(CFLAGS) $(MDL)/regtest.cpp -o regtest

.PHONY: clean
clean : 
	rm *.o *.out regtest gpiotest





# # gpiotest
# gpiotest : gpiotest.o gpio.o register.o
# 	$(CC) $(CFLAGS) -o gpiotest gpiotest.o gpio.o register.o
# 	rm *.o
# 	./gpiotest

# gpiotest.o : $(MDL)/gpiotest.cpp gpio.o register.o
# 	$(CC) $(CFLAGS) -c $(MDL)/gpiotest.cpp

# gpio.o: $(SRC)/gpio.cpp register.o
# 	$(CC) $(CFLAGS) -c $(SRC)/gpio.cpp



# # AVR settings
# AVR_CC = avr-g++
# AVR_MCU = atmega328p
# AVR_PRM = -mmcu=$(AVR_MCU) -ansi -pedantic-errors -Wall -Wextra -Wcpp -I ${INCLUDE}

# OBJS = avr_firmware.o register.o sysclk.o uart.o gpio.o
# avr_firmware.hex : $(OBJS)
# 	$(AVR_CC) $(AVR_PRM) $(OBJS) -o avr_firmware.hex

# OBJS = $(MDL)/avr_firmware.c register.o sysclk.o uart.o gpio.o
# avr_firmware.o : $(OBJS)
# 	$(AVR_CC) $(AVR_PRM) -c $(OBJS)


# #! /bin/bash
# dev_path="/dev/bus/usb/001/012"
# parn_num="m328p"
# fuse_set="-U lfuse:w:0xee:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m"
# firmware_file="firmware.hex"
# avrdude -c usbasp -P $dev_path -p $parn_num -F -v $fuse_set -U flash:w:$firmware_file