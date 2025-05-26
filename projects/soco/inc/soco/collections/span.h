#pragma once

#include "soco/collections/iterator.h"


typedef struct
{
	soco_iterator* beg;
	soco_iterator* end;
} soco_span;
