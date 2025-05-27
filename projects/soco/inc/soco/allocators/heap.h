#pragma once

#include "soco/allocators/allocator.h"

typedef struct
{
} soco_allocator_heap;

void* soco_allocator_heap_alloc(soco_allocator_heap* allocator, size_t size_byte);
void soco_allocator_heap_dealloc(soco_allocator_heap* allocator, void* mem_ptr);


soco_allocator soco_as_allocator(soco_allocator_heap* alloc_heap);

