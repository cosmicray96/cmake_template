#include <stdio.h>
#include "soco/soco.h"

int main() {
	int result = soco_add(1, 2);	
	if(result == 3) {
		return 0;	
	}
	return 1;
}
