#pragma once

#include "soco_dsa/collections/iterator.h"
#include "soco_dsa/soco_dsa.h"
#include "soco_dsa/collections/collection.h"
#include "soco_dsa/allocators/allocator.h"


typedef struct
{
	soco_dsa_byte* data;
	size_t count;
	size_t capacity;
	size_t elem_size_byte;
} soco_dsa_array;

soco_dsa_array soco_dsa_array_construct(size_t capacity, size_t ele_size_byte, soco_dsa_allocator* allocator);
void soco_dsa_array_deconstruct(soco_dsa_array* array, soco_dsa_allocator* allocator);


void soco_dsa_array_write_at(soco_dsa_array* array, void* data, size_t index);
void* soco_dsa_array_read_at(soco_dsa_array* array, size_t index);

size_t soco_dsa_array_capacity(soco_dsa_array* array);
size_t soco_dsa_array_count(soco_dsa_array* array);


//collections
soco_dsa_collection soco_dsa_as_collection(soco_dsa_array* array);


// iterators
#include "soco_dsa/collections/iterator.h"

typedef struct
{
	soco_dsa_array* array;
	size_t index;
} soco_dsa_array_iterator;


soco_dsa_array_iterator soco_dsa_array_iterator_construct(soco_dsa_array* array, size_t index);

soco_dsa_array_iterator copy(soco_dsa_array_iterator* it);

size_t soco_dsa_array_iterator_elem_size_byte(soco_dsa_array_iterator* it);

void soco_dsa_array_iterator_inc(soco_dsa_array_iterator* it);

void* soco_dsa_array_iterator_get(soco_dsa_array_iterator* it); 

bool soco_dsa_array_iterator_equal(soco_dsa_array_iterator* it1, soco_dsa_array_iterator* it2); 


// // array iterator to iterator
soco_dsa_iterator soco_dsa_as_iterator(soco_dsa_array_iterator* it);

