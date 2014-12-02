#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	PQ_ComplHeap * pq = initPQ(10 * sizeof(int));
	for(i = 0; i < 9 ;i++)
		insertPQ(i,pq);
	printVector(pq->vector);
	return 0;
}