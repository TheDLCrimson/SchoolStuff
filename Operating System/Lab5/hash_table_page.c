#include <stdio.h>
#include <stdlib.h>
#define PAGE_SIZE 4096 
#define NUM_ENTRIES 100 


typedef struct PageTableEntry {
    unsigned long long virtual_address; 
    unsigned long long physical_address;
    int valid; 
    struct PageTableEntry* next; 
} page_table_entry_t;


page_table_entry_t* hash_table[NUM_ENTRIES];
int page_fault_count = 0; 


unsigned int hash(unsigned long long virtual_page) {
    return virtual_page % NUM_ENTRIES; 
}


void initialize_hash_table() {
    for (int i = 0; i < NUM_ENTRIES; i++) {
        hash_table[i] = NULL;
    }
}


void insert(unsigned long long virtual_address, unsigned long long physical_address) {
    unsigned long long virtual_page = virtual_address / PAGE_SIZE; 
    unsigned int index = hash(virtual_page); 

    
    page_table_entry_t* new_entry = (page_table_entry_t*)malloc(sizeof(page_table_entry_t));
    new_entry->virtual_address = virtual_address;
    new_entry->physical_address = physical_address;
    new_entry->valid = 1;   
    new_entry->next = NULL; 

    
    if (hash_table[index] == NULL) {
        hash_table[index] = new_entry;  
    } else {
        new_entry->next = hash_table[index];
        hash_table[index] = new_entry;
    }
}


unsigned long long lookup(unsigned long long virtual_address) {
    unsigned long long virtual_page = virtual_address / PAGE_SIZE; 
    unsigned int index = hash(virtual_page); 

    
    page_table_entry_t* current = hash_table[index];
    while (current != NULL) {
        if (current->valid && current->virtual_address == virtual_address) {
            return current->physical_address; 
        }
        current = current->next;
    }

    
    page_fault_count++;
    printf("Page fault for virtual address 0x%llX\n", virtual_address);
    return -1; 
}


void free_hash_table() {
    for (int i = 0; i < NUM_ENTRIES; i++) {
        page_table_entry_t* current = hash_table[i];
        while (current != NULL) {
            page_table_entry_t* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    initialize_hash_table();

    
    insert(0x1000, 0x2000);
    insert(0x2000, 0x3000);
    insert(0x3000, 0x4000);
    insert(0x1000000000001000, 0x6000); 
    insert(0x1000000000002000, 0x7000);
    insert(0x1000000000003000, 0x8000);

    printf("=== Valid Mappings ===\n");
    unsigned long long physical_address = lookup(0x1000);
    if (physical_address != -1) 
        printf("Physical address for 0x1000: 0x%llX\n", physical_address);
    
    physical_address = lookup(0x2000);
    if (physical_address != -1) 
        printf("Physical address for 0x2000: 0x%llX\n", physical_address);
    
    physical_address = lookup(0x1000000000001000);
    if (physical_address != -1) 
        printf("Physical address for 0x1000000000001000: 0x%llX\n", physical_address);
    
    physical_address = lookup(0x1000000000002000);
    if (physical_address != -1) 
        printf("Physical address for 0x1000000000002000: 0x%llX\n", physical_address);
    
    physical_address = lookup(0x1000000000003000);
    if (physical_address != -1) 
        printf("Physical address for 0x1000000000003000: 0x%llX\n", physical_address);
    
    printf("\n=== Unmapped Addresses ===\n");
    physical_address = lookup(0x5000); 
    if (physical_address == -1) 
        printf("Page fault for 0x5000\n");
    
    physical_address = lookup(0x4000); 
    if (physical_address == -1) 
        printf("Page fault for 0x4000\n");
    
    physical_address = lookup(0x0000000100000000);
    if (physical_address == -1) 
        printf("Page fault for 0x0000000100000000\n");
    
    physical_address = lookup(0xFFFFFFFFFFFFFFFF);
    if (physical_address == -1) 
        printf("Page fault for 0xFFFFFFFFFFFFFFFF\n");
    
    physical_address = lookup(0x00000000DEADBEEF);
    if (physical_address == -1) 
        printf("Page fault for 0x00000000DEADBEEF\n");
    
    printf("\n=== Colliding Addresses ===\n");
    insert(0x0000000000001010, 0x5000); 
    insert(0x0000000000011010, 0x6000); 

    physical_address = lookup(0x0000000000001010);
    if (physical_address != -1) 
        printf("Physical address for 0x0000000000001010: 0x%llX\n", physical_address);

    physical_address = lookup(0x0000000000011010);
    if (physical_address != -1) 
        printf("Physical address for 0x0000000000011010: 0x%llX\n", physical_address);
    
    printf("Total page faults: %d\n", page_fault_count);

    free_hash_table();
    return 0;
}
