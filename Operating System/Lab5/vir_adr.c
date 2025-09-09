#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096 
#define OFFSET_BITS 12 

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: %s <virtual_address>\n", argv[0]);
        return 1;
    }

    unsigned int virtual_address = (unsigned int)strtoul(argv[1], NULL, 10);
    
    unsigned int page_number = virtual_address >> OFFSET_BITS; 
    unsigned int offset = virtual_address & (PAGE_SIZE - 1);    

    printf("The address %u contains:\n", virtual_address);
    printf("Page number = %u\n", page_number);
    printf("Offset = %u\n", offset);

    return 0;
}
