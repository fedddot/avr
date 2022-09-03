#! /bin/bash
headers_path="./include"
sources_path="./src"
source_files="$sources_path/register.cpp $sources_path/gpio.cpp $sources_path/sysclk.cpp lyn_test.cpp"
output_file="lyn_test.o"

clear
rm -v $output_file
g++ -ansi -pedantic-errors -Wall -Wextra -Wcpp -I $headers_path $source_files -o $output_file