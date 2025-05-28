#pragma once

#include "soco_dsa/soco_dsa.h"

typedef struct soco_dsa_allocator_vt_for_heap soco_dsa_allocator_vt;

typedef struct
{
	soco_dsa_allocator_vt* vt;
	void* dt;
} soco_dsa_allocator;

struct soco_dsa_allocator_vt_for_heap
{
	void* (*alloc)(soco_dsa_allocator* allocator, size_t size_byte);
	void (*dealloc)(soco_dsa_allocator* allocator, void* mem_ptr);
};

