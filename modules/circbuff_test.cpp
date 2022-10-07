#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circbuff.h"

#define BUFF_SIZE 10

int main(void) {
    CircularBuffer buff = CircularBuffer(BUFF_SIZE);
    char str1[] = "Kekeke";
    char str2[] = "0123456789101112";
    char *dest = (char *)malloc(BUFF_SIZE * sizeof(char));
    size_t bytes_read = 0;

    printf("Starting test ...\n");

    printf("buff capacity = %lu\n", buff.get_capacity());
    printf("buff size = %lu\n", buff.get_size());
    
    printf("Inserting string \"%s\"...\n", str1);
    buff.write_bytes(str1, 6);
    printf("buff size = %lu\n", buff.get_size());

    printf("Reading 10 bytes from the buff ...\n");
    bytes_read = buff.read_bytes(dest, BUFF_SIZE);
    printf("%lu bytes read\n", bytes_read);
    printf("string read: \"%s\"\n", dest);
    printf("buff size = %lu\n", buff.get_size());

    printf("\n\nInserting string \"%s\"...\n", str2);
    buff.write_bytes(str2, strlen(str2));
    printf("buff size = %lu\n", buff.get_size());

    printf("Reading 6 bytes from the buff ...\n");
    bytes_read = buff.read_bytes(dest, 6);
    printf("%lu bytes read\n", bytes_read);
    printf("string read: \"%s\"\n", dest);
    printf("buff size = %lu\n", buff.get_size());

    printf("Reading 4 bytes from the buff ...\n");
    bytes_read = buff.read_bytes(dest, 4);
    printf("%lu bytes read\n", bytes_read);
    printf("string read: \"%s\"\n", dest);
    printf("buff size = %lu\n", buff.get_size());



    return 0;
}