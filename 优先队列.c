#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	PQ_ComplHeap * pq = initPQ(10 * sizeof(int));
	PQ_ComplHeap * pq1 = initPQ(10 * sizeof(int));
	for(i = 0; i < 20 ;i++)
		insertPQ(i,pq);
	for(i = 0; i < 20 ;i++)
		insertPQ(i,pq1);
	printVector(pq->vector);
	printf("\n");
	printVector(pq1->vector);
	return 0;
}