#pragma once

#include "p04_coll/collections.h"

#include <stdint.h>


typedef struct {
	byte* data;
	size_t length;
	size_t capacity;
	size_t ele_size_byte;
} p04_array;

static p04_array p04_coll_array_construct(size_t capacity, size_t ele_size_byte)
{
	p04_array a = {
		.data=malloc(capacity * ele_size_byte),
		.length=0,
		.capacity=capacity,
		.ele_size_byte=ele_size_byte
	};
	*(((int32_t*)(a.data)) + 2) = 96; 
	*(((int32_t*)(a.data)) + 3) = 123; 
	return a;
}

static void p04_coll_array_destruct(p04_array* array)
{
	free(array->data);
}

static byte* p04_coll_array_at(void* coll, size_t index)
{
	p04_array* array = (p04_array*)coll;

	return (byte*)&(array->data[index * array->ele_size_byte]);
}



extern p04_coll_randacc_vtable p04_coll_array_randacc_vtable; 
static p04_coll_randacc p04_as_coll_randacc(p04_array* array)
{
	p04_coll_randacc randacc;
	randacc.vt = &p04_coll_array_randacc_vtable;
	randacc.coll = array;
	return randacc;
}
