#pragma once

#include "soco/soco.h"

typedef struct soco_collection_vt soco_collection_vt;

typedef struct 
{
	struct soco_collection_vt* vt;
	void* dt;
} soco_collection;

struct soco_collection_vt
{
	size_t (*count)(void* clctn);
};



soco_collection* soco_collection_foreach(soco_collection* clctn, void (*f)(void* elem));
