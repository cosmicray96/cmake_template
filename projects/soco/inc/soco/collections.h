#pragma once

#include "soco/soco.h"


typedef struct 
{
	size_t (*get_size)(void* clctn);
	void* clctn;
} soco_collection;




