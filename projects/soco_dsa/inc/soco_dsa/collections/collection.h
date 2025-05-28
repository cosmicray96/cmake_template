#pragma once

#include "soco_dsa/soco_dsa.h"
#include "soco_dsa/collections/iterator.h"

typedef struct soco_dsa_collection_vt soco_dsa_collection_vt;

typedef struct 
{
	struct soco_dsa_collection_vt* vt;
	void* dt;
} soco_dsa_collection;

struct soco_dsa_collection_vt
{
	size_t (*count)(soco_dsa_collection* clctn);
};



soco_dsa_collection* soco_dsa_collection_foreach(soco_dsa_collection* clctn, void (*f)(void* elem));
