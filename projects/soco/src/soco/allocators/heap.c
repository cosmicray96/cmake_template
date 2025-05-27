#include "soco/allocators/allocator.h"
#include "./soco/allocators/heap.h"


void* soco_allocator_heap_alloc(soco_allocator_heap* allocator, size_t size_byte) {
	return malloc(size_byte);
}

void soco_allocator_heap_dealloc(soco_allocator_heap* allocator, void* mem_ptr) {
	free(mem_ptr);
}


// alllocator

void* soco_allocator_heap_alloc_bridge_allocator(soco_allocator* allocator, size_t size_byte) {
	return soco_allocator_heap_alloc((soco_allocator_heap*)(allocator->dt), size_byte); 
}

void soco_allocator_heap_dealloc_bridge_allocator(soco_allocator* allocator, void* mem_ptr) {
	soco_allocator_heap_dealloc((soco_allocator_heap*)(allocator->dt), mem_ptr);
}

soco_allocator_vt soco_allocator_heap_vt = {
	.alloc=&soco_allocator_heap_alloc_bridge_allocator,
	.dealloc=&soco_allocator_heap_dealloc_bridge_allocator
};
soco_allocator soco_as_allocator(soco_allocator_heap* alloc_heap) {
	soco_allocator alloc = {
		.vt=&soco_allocator_heap_vt,
		.dt=alloc_heap
	};
	return alloc;
}

