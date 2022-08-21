#! /bin/bash
mcu_type="atmega328p"
headers_path="./headers"
sources_path="./sources"
source_files="$sources_path/register.cpp $sources_path/gpio.cpp firmware.cpp"
output_file="firmware.hex"

rm -v $output_file
avr-g++ -mmcu=$mcu_type -ansi -pedantic-errors -Wall -Wextra -Wcpp -I $headers_path $source_files -o $output_file