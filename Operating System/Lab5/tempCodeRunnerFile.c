int main() {
    initialize_hash_table();

    
    insert(0x1000, 0x2000);
    insert(0x2000, 0x3000);
    insert(0x3000, 0x4000);
    insert(0x0000000000001000, 0x6000); 
    insert(0x0000000000002000, 0x7000);
    insert(0x0000000000003000, 0x8000);

    printf("=== Valid Mappings ===\n");
    unsigned long long physical_address = lookup(0x1000);
    if (physical_address != -1) 
        printf("Physical address for 0x1000: 0x%llX\n", physical_address);
    
    physical_address = lookup(0x2000);
    if (physical_address != -1) 
        printf("Physical address for 0x2000: 0x%llX\n", physical_address);
    
    physical_address = lookup(0x0000000000001000);
    if (physical_address != -1) 
        printf("Physical address for 0x0000000000001000: 0x%llX\n", physical_address);
    
    physical_address = lookup(0x0000000000002000);
    if (physical_address != -1) 
        printf("Physical address for 0x0000000000002000: 0x%llX\n", physical_address);
    
    physical_address = lookup(0x0000000000003000);
    if (physical_address != -1) 
        printf("Physical address for 0x0000000000003000: 0x%llX\n", physical_address);
    
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