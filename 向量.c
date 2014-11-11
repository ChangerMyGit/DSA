#include "Vector.h"
#include <stdio.h>

// ¶þ·Ö²éÕÒ µÝ¹é
int BinSearch(int a[],int lo , int hi,int key);
int main(){
	int a[] = {6,202,100,301,38,8,1,201,300,16};
	int i;
	Vector * vec = initVector(10 * sizeof(int));
	for(i = 0;i< (sizeof(a)/sizeof(int));i++)
		insert(vec,a[i]);
	//deleteRange(&vec,1,7);
	printVector(vec);
	printf("\n");
	//insert2(vec,16,2);
	//deleteSingle(vec,9);
    reduplicate(vec);
	printVector(vec);
	printf("\n");
	//sort(vec);
	//bubbleSort(vec);
	//bubbleSort(vec);
	//printVector(vec);
    //printf("\n");
	//uniquify(vec);
	//printVector(vec);
	//printf("\n");
	//printf("%d\n",binSearch(vec,0,13,7));
	//printf("%d\n",binSearch2(vec,0,12,7));
	//printf("%d\n",fibonacciSearch(vec,13));
	//printf("%d\n",binSearch3(vec,2));
	merge(vec,0,vec->size-1);
	printVector(vec);
	printf("\n");
	printf("%d\n",BinSearch((int *)vec->elem,0,vec->size,100));
	return 0;
}

int BinSearch(int a[],int lo , int hi,int key){
	int mi;
	if(lo < hi){
		mi = (lo + hi) >> 1;
		if(a[mi] == key) return mi;
		else if(a[mi] > key) return BinSearch(a,lo,mi,key);
		else if(a[mi] < key) return BinSearch(a,mi+1,hi,key);
	}
	return -1;
}