#pragma once

#include "soco_dsa/collections/iterator.h"


typedef struct
{
	soco_dsa_iterator* beg;
	soco_dsa_iterator* end;
} soco_dsa_span;
