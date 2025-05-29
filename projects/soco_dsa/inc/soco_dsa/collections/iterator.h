#pragma once

#include "./soco_dsa/soco_dsa.h"
#include "./soco_dsa/collections/iterator.h"

typedef struct soco_dsa_iterator_vt soco_dsa_iterator_vt;

typedef struct
{
	soco_dsa_iterator_vt* vt;
	void* dt;
} soco_dsa_iterator;

struct soco_dsa_iterator_vt
{
	soco_dsa_iterator (*copy)(soco_dsa_iterator* it);
	size_t (*elem_size_byte)(soco_dsa_iterator* iter);
	void (*inc)(soco_dsa_iterator* iter);
	void* (*get)(soco_dsa_iterator* iter); // return: get the data that iter points to
	bool (*equal)(soco_dsa_iterator* it1, soco_dsa_iterator* it2);
};

