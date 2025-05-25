#pragma once

#include "soco/soco.h"



typedef struct
{
	void* (*alloc)(void* allocator, size_t size_byte);
	void (*dealloc)(void* allocator, void* mem_ptr);
} soco_allocator_vt;

typedef struct
{
	soco_allocator_vt* vt;
	void* dt;
} soco_allocator;
