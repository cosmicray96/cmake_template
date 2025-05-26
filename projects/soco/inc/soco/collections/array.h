#pragma once

#include "soco/soco.h"
#include "soco/collections/collection.h"
#include "soco/allocators/allocator.h"


typedef struct
{
	soco_byte* data;
	size_t count;
	size_t capacity;
	size_t elem_size_byte;
} soco_array;

soco_array soco_array_construct(size_t capacity, size_t ele_size_byte, soco_allocator* allocator);
void soco_array_deconstruct(soco_array* array, soco_allocator* allocator);


void soco_array_write_at(soco_array* array, void* data, size_t index);
void* soco_array_read_at(soco_array* array, size_t index);

size_t soco_array_capacity(soco_array* array);
size_t soco_array_count(soco_array* array);
