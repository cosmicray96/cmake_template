#pragma once

#include "soco/soco.h"

typedef struct soco_allocator_vt_for_heap soco_allocator_vt;

typedef struct
{
	soco_allocator_vt* vt;
	void* dt;
} soco_allocator;

struct soco_allocator_vt_for_heap
{
	void* (*alloc)(soco_allocator* allocator, size_t size_byte);
	void (*dealloc)(soco_allocator* allocator, void* mem_ptr);
};

