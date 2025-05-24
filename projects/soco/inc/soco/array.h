#pragma once

#include "soco/soco.h"
#include "soco/collections.h"


typedef struct
{
	soco_byte* data;
	size_t length;
	size_t capacity;
	size_t elem_size_byte;
} soco_array;
