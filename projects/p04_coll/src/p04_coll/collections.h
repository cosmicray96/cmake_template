#pragma once

#include "p04_coll/core.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct
{
	size_t (*get_size)();
} p04_collection_vtable;

typedef struct
{
	p04_collection_vtable* vt;
	void* coll;
} p04_collection;



typedef struct
{
	byte* (*at)(void* coll, size_t index);
} p04_coll_randacc_vtable;

typedef struct
{
	p04_coll_randacc_vtable* vt;
	void* coll;
} p04_coll_randacc;
