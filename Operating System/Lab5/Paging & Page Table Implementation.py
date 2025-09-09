# 1. Calculate the number of entries in a single-level page table
logical_address_bits = 32 
page_size_bits = 13        
number_of_pages = 2 ** (logical_address_bits - page_size_bits) 
print(f"1. Number of entries in a single-level page table: {number_of_pages} entries")

# 2. Calculate the time for a paged memory reference
memory_reference_time_ns = 30  
paged_memory_reference_time_ns = memory_reference_time_ns * 2  # Two accesses: page table and physical memory
print(f"2. Time for a paged memory reference: {paged_memory_reference_time_ns} ns")
