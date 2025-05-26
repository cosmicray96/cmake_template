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




// iterators

soco_array_iterator soco_array_iterator_construct(soco_array* array, size_t index) {
soco_array_iterator iter; 
	iter.array = array;
	iter.index = index;
	return iter;
}


void soco_array_iterator_inc(void* iter) {
	soco_array_iterator* it = (soco_array_iterator*)iter;
	it->index++;
}

void* soco_array_iterator_get(void* iter) {
	soco_array_iterator* it = (soco_array_iterator*)iter;
	return it->array->data + (it->array->elem_size_byte * it->index);
}

bool soco_array_iterator_equal(void* it1, void* it2) {
	soco_array_iterator* iter1 = (soco_array_iterator*)it1;
	soco_array_iterator* iter2 = (soco_array_iterator*)it2;
	return iter1->index == iter2->index;
}

soco_iterator_vt soco_array_iterator_vt = {
	.inc=&soco_array_iterator_inc,
	.get=&soco_array_iterator_get,
	.equal=&soco_array_iterator_equal,
};

// // array iterator to iterator
soco_iterator_vt soco_array_iterator_iterator_vt = {
	.get=&soco_array_iterator_get,
	.equal=&soco_array_iterator_equal,
	.inc=&soco_array_iterator_inc
};
soco_iterator soco_as_iterator(soco_array_iterator* iter) {
	soco_iterator it = {
		.vt=&soco_array_iterator_iterator_vt,
		.dt=iter
	}; 	
	return it;
}
