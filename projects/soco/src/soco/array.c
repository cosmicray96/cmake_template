#include "soco/array.h"
#include <string.h>


soco_array soco_array_construct(size_t capacity, size_t ele_size_byte, soco_allocator* allocator) {
	soco_array a = {
		.capacity=capacity,
		.count=0,
		.elem_size_byte=ele_size_byte,
		.data=allocator->vt->alloc(allocator, capacity*ele_size_byte)
	};	
	return a;
}

void soco_array_deconstruct(soco_array* array, soco_allocator* allocator) {
	allocator->vt->dealloc(allocator, array->data);	
}


void soco_array_write_at(soco_array* array, void* data, size_t index) {
	size_t new_count = index+1;
	if(array->count < new_count) {
		array->count = new_count;
	}	

	memcpy((array->data + (index*array->elem_size_byte)), data, array->elem_size_byte);
}

void* soco_array_read_at(soco_array* array, size_t index) {
	return (array->data + (index * array->elem_size_byte));
}

size_t soco_array_capacity(soco_array* array) {
	return array->capacity;
}

size_t soco_array_count(soco_array* array) {
	return array->count;
}
