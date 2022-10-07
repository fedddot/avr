#include <stdio.h>
#include <stdlib.h>

#include "circbuff.h"

#define BUFF_SIZE 10

int main(void) {
    CircularBuffer buff = CircularBuffer(BUFF_SIZE);
    char str[] = "Kekeke";
    char *dest = (char *)malloc(BUFF_SIZE * sizeof(char));
    size_t bytes_read = 0;

    printf("Starting test ...\n");

    printf("buff capacity = %lu\n", buff.get_capacity());
    printf("buff size = %lu\n", buff.get_size());
    
    printf("Inserting string \"%s\"...\n", str);
    buff.write_bytes(str, 6);

    printf("Reading 10 bytes from the buff ...");
    bytes_read = buff.read_bytes(dest, BUFF_SIZE);
    printf("%lu bytes read\n", bytes_read);
    printf("string read: \"%s\"\n", dest);

    return 0;
}