#include <soco_dsa/allocators/allocator.h>
#include <soco_dsa/allocators/heap.h>
#include <soco_dsa/collections/span.h>
#include <soco_dsa/collections/iterator.h>
#include <soco_dsa/collections/array.h>
#include <soco_dsa/algo/algo.h>


#include <assert.h>

bool min_func(void* elem1, void* elem2) {
	return (*((int32_t*)elem1)) < (*((int32_t*)elem2));
}


int main() {
	soco_dsa_allocator_heap allocator_heap;
	soco_dsa_allocator allocator = soco_dsa_as_allocator(&allocator_heap);
	soco_dsa_array array = soco_dsa_array_construct(5, 4, &allocator);


	int32_t data1 = 10;
	soco_dsa_array_write_at(&array, &data1, 0);
	int32_t data2 = 15;
	soco_dsa_array_write_at(&array, &data2, 1);
	int32_t data3 = 5;
	soco_dsa_array_write_at(&array, &data3, 2);
	int32_t data4 = 20;
	soco_dsa_array_write_at(&array, &data4, 3);
	int32_t data5 = 10;
	soco_dsa_array_write_at(&array, &data5, 4);


	soco_dsa_array_iterator it1 = soco_dsa_array_iterator_construct(&array, 0);
	soco_dsa_array_iterator it2 = soco_dsa_array_iterator_construct(&array, soco_dsa_array_count(&array));
	soco_dsa_iterator iter1 = soco_dsa_as_iterator(&it1);
	soco_dsa_iterator iter2 = soco_dsa_as_iterator(&it2);
	soco_dsa_span span = {
		.beg=&iter1,
		.end=&iter2
	};

	assert(soco_dsa_min(span, &min_func) == 2);
}
