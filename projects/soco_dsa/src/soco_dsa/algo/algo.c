#include "soco_dsa/algo/algo.h"
#include "soco_dsa/allocators/allocator.h"
#include "soco_dsa/collections/iterator.h"

#include <string.h>

// assumed collection size atleast 1
size_t soco_dsa_min(soco_dsa_span span, bool (*comp_func)(void* elem1, void* elem2)) {

	soco_dsa_iterator it1 = *(span.beg);
	soco_dsa_iterator it2 = *(span.beg);
	size_t min_index = 0;
	
	it2.vt->inc(&it2);
	if(it2.vt->equal(&it2, span.end)) {
		return min_index;
	}

	for(size_t index=0; !it1.vt->equal(&it2, span.end); index++) {
		bool result = comp_func(it1.vt->get(&it1), it2.vt->get(&it2));
		if(result) {
			min_index = index;
		}

		it1.vt->inc(&it1);	
		it2.vt->inc(&it2);	
	}
	return min_index;
}

size_t soco_dsa_max(soco_dsa_span span, bool (*comp_func)(void* elem1, void* elem2)) {
	return 0;
}

void* soco_dsa_dsa_sum(soco_dsa_span span, void* (*add_func)(void* elem1, void* elem2)) {
	return NULL;
}

void* soco_dsa_sum(soco_dsa_span span, void* (*add_func)(void* elem1, void* elem2)) {
	return NULL;
}
