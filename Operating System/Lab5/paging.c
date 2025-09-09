#include <stdio.h>

int main() {
    // Constants for the problem
    unsigned int logical_address_space = 65536;  // Logical address space (2^16 bytes)
    unsigned int page_size = 1024;               // Page size (2^10 bytes = 1 KB)
    unsigned int physical_address_space = 16384; // Physical address space (2^14 bytes = 16 KB)
    unsigned int logical_address = 0x3A2F;       // Logical address (hex)
    unsigned int frame_number = 10;              // Frame number (as given)

    // Step 1: Calculate the number of pages in the logical address space
    unsigned int num_pages = logical_address_space / page_size;

    // Step 2: Calculate the number of frames in the physical address space
    unsigned int num_frames = physical_address_space / page_size;

    // Step 3: Calculate the page number and offset manually
    unsigned int page_number = logical_address / page_size; // Page number = integer division
    unsigned int offset = logical_address % page_size;      // Offset = remainder

    // Step 4: Calculate the physical address
    unsigned int frame_base_address = frame_number * page_size;
    unsigned int physical_address = frame_base_address + offset;

    // Output results
    printf("Paging and Address Translation Results:\n");
    printf("1. Number of Pages in Logical Address Space: %u\n", num_pages);
    printf("2. Number of Frames in Physical Address Space: %u\n", num_frames);
    printf("3. Page Number: %u\n", page_number);
    printf("4. Offset: %u\n", offset);
    printf("5. Physical Address (decimal): %u\n", physical_address);
    printf("6. Physical Address (hex): 0x%X\n", physical_address);

    return 0;
}
