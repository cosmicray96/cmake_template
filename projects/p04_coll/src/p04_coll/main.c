#include "p04_coll/array.h"
#include <stdio.h>

int main() {
	
	p04_array a = p04_coll_array_construct(10, 4);

	int32_t* ele = ((int32_t*)p04_as_coll_randacc(&a).vt->at(&a, 2));
	int32_t* ele2  = ((int32_t*)p04_as_coll_randacc(&a).vt->at(&a, 3));	
	

	printf("element at 2: %d\n", *ele);
	printf("element at 3: %d\n", *ele2);

	return 0;
}


