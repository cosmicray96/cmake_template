#pragma once

#include "./soco/soco.h"
#include "./soco/collections/iterator.h"

typedef struct soco_iterator_vt soco_iterator_vt;

typedef struct
{
	soco_iterator_vt* vt;
	void* dt;
} soco_iterator;

struct soco_iterator_vt
{
	void (*inc)(soco_iterator* iter);
	void* (*get)(soco_iterator* iter); // return: get the data that iter points to
	bool (*equal)(soco_iterator* it1, soco_iterator* it2);
};

