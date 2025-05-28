#pragma once

#include "soco_dsa/allocators/allocator.h"

typedef struct
{
} soco_dsa_allocator_heap;

void* soco_dsa_allocator_heap_alloc(soco_dsa_allocator_heap* allocator, size_t size_byte);
void soco_dsa_allocator_heap_dealloc(soco_dsa_allocator_heap* allocator, void* mem_ptr);


soco_dsa_allocator soco_dsa_as_allocator(soco_dsa_allocator_heap* alloc_heap);

