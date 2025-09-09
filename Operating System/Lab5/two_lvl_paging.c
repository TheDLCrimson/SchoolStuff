#include <stdio.h>
#include <stdlib.h>

#define ULL unsigned long long
#define PAGE_SIZE 4096UL                                                           // Page size (4 KB)
#define PAGE_TABLE_SIZE 1024UL                                                     // Number of entries in each page table
#define PAGE_DIRECTORY_SIZE 1024UL                                                 // Number of entries in the page directory
#define PHYSICAL_MEMORY_SIZE 4294967296ULL // Total memory size

// Page directory entry and page table entry types
typedef ULL pte_t; // Page Table Entry
typedef ULL pde_t; // Page Directory Entry

// Simulate physical memory
unsigned char *physical_memory;

// Page directory and page tables
pde_t page_directory[PAGE_DIRECTORY_SIZE]; // Page directory
pte_t *page_table[PAGE_DIRECTORY_SIZE];    // Array of pointers to page tables

// Function to initialize the page tables and directory
void initialize_paging()
{
    physical_memory = malloc((size_t)PHYSICAL_MEMORY_SIZE);
    if (physical_memory == NULL) {
        printf("Error: Unable to allocate physical memory.\n");
        exit(1);
    }
    // Simulate 1024 page tables, each with 1024 entries
    for (int i = 0; i < PAGE_DIRECTORY_SIZE; i++)
    {
        page_directory[i] = i * PAGE_TABLE_SIZE;                          // Map each directory entry to a page table
        page_table[i] = (pte_t *)malloc(PAGE_TABLE_SIZE * sizeof(pte_t)); // Allocate memory for the page table

        // Simulate filling each page table with physical frames
        for (int j = 0; j < PAGE_TABLE_SIZE; j++)
        {
            page_table[i][j] = (i * PAGE_TABLE_SIZE + j) * PAGE_SIZE; // Map each page table entry to a physical frame
        }
    }
}

// Function to translate a virtual address to a physical address
ULL translate_address(ULL virtual_address)
{
    // Split the virtual address into page directory index, page table index, and offset
    ULL page_directory_index = (virtual_address >> 22) & 0x3FF; // Top 10 bits for page directory index
    ULL page_table_index = (virtual_address >> 12) & 0x3FF;     // Next 10 bits for page table index
    ULL offset = virtual_address & 0xFFF;                       // Last 12 bits for offset

    // Retrieve the page table pointer from the page directory
    pte_t *page_table_ptr = page_table[page_directory_index];

    // Check if the page table exists (page directory entry is valid)
    if (page_table_ptr == NULL)
    {
        printf("Invalid page directory entry!\n");
        return -1; // Indicate an invalid mapping
    }

    // Retrieve the physical address from the page table
    ULL physical_address = page_table_ptr[page_table_index] + offset;

    // Return the translated physical address
    return physical_address;
}

// Function to simulate accessing physical memory
void access_physical_memory(ULL physical_address)
{
    // Debugging 
    printf("Checking PHYSICAL_MEMORY_SIZE: %llu\n", PHYSICAL_MEMORY_SIZE);
    printf("Checking physical address: %llu\n", physical_address);
    // Check if the physical address is within the allocated memory space
    if (physical_address < PHYSICAL_MEMORY_SIZE)
    {
        printf("IF branch entered: Physical address is within bounds.\n"); // Indicate that a number is too big to be simulated in array
        physical_memory[physical_address] = 1; // Mark the memory as accessed
        printf("Accessed physical memory at address: 0x%X\n", physical_address);
    }
    else
    {
        printf("ELSE branch entered: Physical address is invalid.\n"); // Indicate that a number is too big to be simulated in array
        printf("Invalid physical address: 0x%X\n", physical_address);
    }
}

int main()
{
    // Initialize the page directory and page tables
    initialize_paging();

    // Example virtual address to be translated
    ULL virtual_address = 0x12345678;

    // Print the virtual address
    printf("Virtual Address: 0x%X\n", virtual_address);

    // Translate the virtual address to a physical address
    ULL physical_address = translate_address(virtual_address);

    // If the translation is valid, access the physical memory
    if (physical_address != (ULL)-1)
    {
        printf("Physical Address: 0x%X\n", physical_address);
        access_physical_memory(physical_address);
    }

    // Free the allocated memory for the page tables
    for (int i = 0; i < PAGE_DIRECTORY_SIZE; i++)
    {
        free(page_table[i]);
    }

    return 0;
}
