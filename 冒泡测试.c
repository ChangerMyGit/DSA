#include "Vector.h"
#include <stdio.h>

int main2(){
	int i ;
	int a[] = {2,3,4,1,5,6,7};
	Vector vec;
	initVector(&vec,10 * sizeof(int));
	for(i = 0;i<7;i++)
		insert(&vec,a[i]);
	insert2(&vec,0,0);
	bubbleSort2(&vec);
	printVector(&vec);
	return 0;
}