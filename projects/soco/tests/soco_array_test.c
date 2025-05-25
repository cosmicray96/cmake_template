#include "soco/allocators/allocator.h"
#include "soco/allocators/heap.h"
#include "soco/array.h"
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

	soco_array_deconstruct(&a, &allocator);
	return 0;
}
