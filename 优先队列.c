#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	PQ_ComplHeap * pq = initPQ(10 * sizeof(int));
	heapify(9,pq);
/*
	for(i = pq->size-1 ; i > 0 ; i--)
		delMax(pq);
	printVector(pq->vector);
*/
	printVector(pq->vector);
	printf("\n");
	heapSort(pq);
	printVector(pq->vector);
	return 0;
}