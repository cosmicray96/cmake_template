#include "soco_dsa/collections/array.h"
#include "soco_dsa/allocators/allocator.h"
#include "soco_dsa/collections/collection.h"
#include "soco_dsa/collections/iterator.h"
#include <string.h>


soco_dsa_array soco_dsa_array_construct(size_t capacity, size_t ele_size_byte, soco_dsa_allocator* allocator) {
	soco_dsa_array a = {
		.capacity=capacity,
		.count=0,
		.elem_size_byte=ele_size_byte,
		.data=allocator->vt->alloc(allocator->dt, capacity*ele_size_byte)
	};	
	return a;
}

void soco_dsa_array_deconstruct(soco_dsa_array* array, soco_dsa_allocator* allocator) {
	allocator->vt->dealloc(allocator->dt, array->data);	
}


void soco_dsa_array_write_at(soco_dsa_array* array, void* data, size_t index) {
	size_t new_count = index+1;
	if(array->count < new_count) {
		array->count = new_count;
	}	

	memcpy((array->data + (index*array->elem_size_byte)), data, array->elem_size_byte);
}

void* soco_dsa_array_read_at(soco_dsa_array* array, size_t index) {
	return (array->data + (index * array->elem_size_byte));
}

size_t soco_dsa_array_capacity(soco_dsa_array* array) {
	return array->capacity;
}

size_t soco_dsa_array_count(soco_dsa_array* array) {
	return array->count;
}


// collection

size_t soco_dsa_array_count_bridge_collection(soco_dsa_collection* clctn) {
	soco_dsa_array* array = (soco_dsa_array*)(clctn->dt);
	return soco_dsa_array_count(array);
}

soco_dsa_collection_vt soco_dsa_array_collection_vt = {
	.count=soco_dsa_array_count_bridge_collection
};

soco_dsa_collection soco_dsa_as_collection(soco_dsa_array* array) {
	soco_dsa_collection clctn = {
		.vt=&soco_dsa_array_collection_vt,
		.dt=array
	};	
	return clctn;
}


// array iterator

soco_dsa_array_iterator soco_dsa_array_iterator_construct(soco_dsa_array* array, size_t index) {
soco_dsa_array_iterator it; 
	it.array = array;
	it.index = index;
	return it;
}

soco_dsa_array_iterator soco_dsa_array_iterator_copy(soco_dsa_array_iterator* it) {
	soco_dsa_array_iterator new_it = {
		.array=it->array,
		.index=it->index
	};
	return new_it;
}

size_t soco_dsa_array_iterator_elem_size_byte(soco_dsa_array_iterator* it) {
	return it->array->elem_size_byte;
}

void soco_dsa_array_iterator_inc(soco_dsa_array_iterator* it) {
	it->index++;
}

void* soco_dsa_array_iterator_get(soco_dsa_array_iterator* it) {
	return it->array->data + (it->array->elem_size_byte * it->index);
}

bool soco_dsa_array_iterator_equal(soco_dsa_array_iterator* it1, soco_dsa_array_iterator* it2) {
	return it1->index == it2->index;
}


// array iterator to iterator


soco_dsa_iterator soco_dsa_array_iterator_copy_bridge_iterator(soco_dsa_iterator* it) {
	soco_dsa_array_iterator* array_it = (soco_dsa_array_iterator*)(it->dt);
	soco_dsa_iterator new_it;
	return new_it;
}

size_t soco_dsa_array_iterator_elem_size_byte_bridge_iterator(soco_dsa_iterator* it) {
	soco_dsa_array_iterator* array_it = (soco_dsa_array_iterator*)(it->dt);
	return soco_dsa_array_iterator_elem_size_byte(array_it);
}

void soco_dsa_array_iterator_inc_bridge_iterator(soco_dsa_iterator* it) {
	soco_dsa_array_iterator* array_it = (soco_dsa_array_iterator*)(it->dt);
	soco_dsa_array_iterator_inc(array_it);
}

void* soco_dsa_array_iterator_get_bridge_iterator(soco_dsa_iterator* it) {
	soco_dsa_array_iterator* array_it = (soco_dsa_array_iterator*)(it->dt);
	return soco_dsa_array_iterator_get(array_it);
}

bool soco_dsa_array_iterator_equal_bridge_iterator(soco_dsa_iterator* it1, soco_dsa_iterator* it2) {
	soco_dsa_array_iterator* array_it1 = (soco_dsa_array_iterator*)(it1->dt);
	soco_dsa_array_iterator* array_it2 = (soco_dsa_array_iterator*)(it2->dt);
	return soco_dsa_array_iterator_equal(array_it1, array_it2);
}

soco_dsa_iterator_vt soco_dsa_array_iterator_iterator_vt = {
	.elem_size_byte=&soco_dsa_array_iterator_elem_size_byte_bridge_iterator,
	.get=&soco_dsa_array_iterator_get_bridge_iterator,
	.equal=&soco_dsa_array_iterator_equal_bridge_iterator,
	.inc=&soco_dsa_array_iterator_inc_bridge_iterator
};
soco_dsa_iterator soco_dsa_as_iterator(soco_dsa_array_iterator* array_it) {
	soco_dsa_iterator it = {
		.vt=&soco_dsa_array_iterator_iterator_vt,
		.dt=array_it
	}; 	
	return it;
}

