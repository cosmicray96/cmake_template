#include "soco/allocators/allocator.h"
#include "soco/allocators/heap.h"
#include "soco/collections/array.h"
#include "soco/collections/collection.h"
#include <assert.h>

int main()
{
	soco_allocator_heap alloc_heap;
	soco_allocator allocator = soco_as_allocator(&alloc_heap);

	soco_array a = soco_array_construct(10, 4, &allocator);

	assert(soco_array_capacity(&a) == 10);
	assert(soco_array_count(&a) == 0);

	int32_t data1 = 123;
	soco_array_write_at(&a, &data1, 0);
	assert(*(int32_t*)soco_array_read_at(&a, 0) == 123);
	assert(soco_array_count(&a) == 1);


	int32_t data2 = 456;
	soco_array_write_at(&a, &data2, 8);
	assert(*(int32_t*)soco_array_read_at(&a, 8) == 456);
	assert(soco_array_count(&a) == 9);

	int32_t data3 = 789;
	soco_array_write_at(&a, &data3, 2);
	assert(*(int32_t*)soco_array_read_at(&a, 2) == 789);
	assert(soco_array_count(&a) == 9);
	
	soco_array_iterator iter1 = soco_array_iterator_construct(&a, 0);
	assert(iter1.index == 0);
	assert(iter1.array == &a);

	soco_array_iterator iter2 = soco_array_iterator_construct(&a, 9);

	soco_iterator it1 = soco_as_iterator(&iter1);
	soco_iterator it2 = soco_as_iterator(&iter2);

	assert(!it1.vt->equal(it1.dt, it2.dt));

	it1.vt->inc(it1.dt);	
	it1.vt->inc(it1.dt);

	assert(*(int32_t*)(it1.vt->get(it1.dt)) == 789);

	soco_array_deconstruct(&a, &allocator);
	return 0;
}
