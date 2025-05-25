#include "soco/allocators/allocator.h"
#include "./soco/allocators/heap.h"


void* soco_allocator_heap_alloc(void* allocator, size_t size_byte) {
	return malloc(size_byte);
}

void soco_allocator_heap_dealloc(void* allocator, void* mem_ptr) {
	free(mem_ptr);
}


soco_allocator_vt soco_allocator_vt_for_heap = {
	.alloc=&soco_allocator_heap_alloc,
	.dealloc=&soco_allocator_heap_dealloc
};
soco_allocator soco_as_allocator(soco_allocator_heap* alloc_heap) {
	soco_allocator alloc = {
		.vt=&soco_allocator_vt_for_heap,
		.dt=alloc_heap
	};
	return alloc;
}

