#include "soco/collections/array.h"
#include "soco/allocators/allocator.h"
#include "soco/collections/iterator.h"
#include <string.h>


soco_array soco_array_construct(size_t capacity, size_t ele_size_byte, soco_allocator* allocator) {
	soco_array a = {
		.capacity=capacity,
		.count=0,
		.elem_size_byte=ele_size_byte,
		.data=allocator->vt->alloc(allocator->dt, capacity*ele_size_byte)
	};	
	return a;
}

void soco_array_deconstruct(soco_array* array, soco_allocator* allocator) {
	allocator->vt->dealloc(allocator->dt, array->data);	
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




// array iterator

soco_array_iterator soco_array_iterator_construct(soco_array* array, size_t index) {
soco_array_iterator it; 
	it.array = array;
	it.index = index;
	return it;
}


void soco_array_iterator_inc(soco_array_iterator* it) {
	it->index++;
}

void* soco_array_iterator_get(soco_array_iterator* it) {
	return it->array->data + (it->array->elem_size_byte * it->index);
}

bool soco_array_iterator_equal(soco_array_iterator* it1, soco_array_iterator* it2) {
	return it1->index == it2->index;
}


// // iterator


void soco_array_iterator_inc_bridge_iterator(soco_iterator* it) {
	soco_array_iterator* array_it = (soco_array_iterator*)(it->dt);
	soco_array_iterator_inc(array_it);
}

void* soco_array_iterator_get_bridge_iterator(soco_iterator* it) {
	soco_array_iterator* array_it = (soco_array_iterator*)(it->dt);
	return soco_array_iterator_get(array_it);
}

bool soco_array_iterator_equal_bridge_iterator(soco_iterator* it1, soco_iterator* it2) {
	soco_array_iterator* array_it1 = (soco_array_iterator*)(it1->dt);
	soco_array_iterator* array_it2 = (soco_array_iterator*)(it2->dt);
	return soco_array_iterator_equal(array_it1, array_it2);
}


// // array iterator to iterator
soco_iterator_vt soco_array_iterator_iterator_vt = {
	.get=&soco_array_iterator_get_bridge_iterator,
	.equal=&soco_array_iterator_equal_bridge_iterator,
	.inc=&soco_array_iterator_inc_bridge_iterator
};
soco_iterator soco_as_iterator(soco_array_iterator* array_it) {
	soco_iterator it = {
		.vt=&soco_array_iterator_iterator_vt,
		.dt=array_it
	}; 	
	return it;
}
