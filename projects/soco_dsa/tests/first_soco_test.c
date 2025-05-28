#include <stdio.h>
#include "soco_dsa/soco_dsa.h"

int main() {
	int result = soco_dsa_add(1, 2);	
	if(result == 3) {
		return 0;	
	}
	return 1;
}
