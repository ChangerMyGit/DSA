#include "Vector.h"
#include <stdio.h>

int main(){
	int a[] = {6,202,100,301,38,8,1};
	int i;
	Vector vec;
	initVector(&vec,10 * sizeof(int));
	for(i=0;i< (sizeof(a)/sizeof(int));i++)
		insert(&vec,a[i]);
	//deleteRange(&vec,1,7);
	printVector(&vec);
	printf("\n");
	//insert2(&vec,16,2);
	//deleteSingle(&vec,9);
	//reduplicate(&vec);
	//printVector(&vec);
	//sort(&vec);
	//bubbleSort(&vec);
	//bubbleSort(&vec);
	//printVector(&vec);
    //printf("\n");
	//uniquify(&vec);
	//printVector(&vec);
	//printf("\n");
	//printf("%d\n",binSearch(&vec,0,13,7));
	//printf("%d\n",binSearch2(&vec,0,12,7));
	//printf("%d\n",fibonacciSearch(&vec,13));
	//printf("%d\n",binSearch3(&vec,2));
	merge(&vec,0,vec.size-1);
	printVector(&vec);
	printf("\n");
	return 0;
}