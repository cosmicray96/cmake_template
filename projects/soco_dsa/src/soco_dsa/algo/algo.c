#include "soco_dsa/algo/algo.h"
#include "soco_dsa/allocators/allocator.h"
#include "soco_dsa/collections/iterator.h"

#include <string.h>

// assumed collection size atleast 1
size_t soco_dsa_min(soco_dsa_span span, bool (*comp_func)(void* elem1, void* elem2)) {

	soco_dsa_iterator it_cur_min = *(span.beg);
	soco_dsa_iterator it_cur = *(span.beg);
	size_t min_index = 0;
	
	it_cur.vt->inc(&it_cur);
	if(it_cur.vt->equal(&it_cur, span.end)) {
		return min_index;
	}
	for(size_t index=1; !it_cur.vt->equal(&it_cur, span.end); index++) {
		bool result = comp_func(it_cur.vt->get(&it_cur), it_cur_min.vt->get(&it_cur_min));
		if(result) {
			min_index = index;
			it_cur_min = it_cur; // error, needs a copy function
		}
		it_cur.vt->inc(&it_cur);	
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
