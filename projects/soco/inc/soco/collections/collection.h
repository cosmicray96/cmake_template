#pragma once

#include "soco/soco.h"

struct soco_collection;

typedef struct
{
	size_t (*count)(void* clctn);
} soco_collection_vt;

typedef struct 
{
	soco_collection_vt* vt;
	void* dt;
} soco_collection;


soco_collection* soco_collection_foreach(soco_collection* clctn, void (*f)(void* elem));
