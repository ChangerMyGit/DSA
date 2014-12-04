#include "PQ.h"
#include "PQ_LeftHeap.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	PQ_ComplHeap * pq = initPQ(10 * sizeof(int));
	LeftHeap * lpq1 = initLeftHeap();
	LeftHeap * lpq2 = initLeftHeap();
	LeftHeap * lpq3 = initLeftHeap();
	heapify(20,pq);
/*
	for(i = pq->size-1 ; i > 0 ; i--)
		delMax(pq);
	printVector(pq->vector);

	printVector(pq->vector);
	printf("\n");
	heapSort(pq);
	printVector(pq->vector);
	printf("\n");
*/    
	insertLeftHeap(17,lpq1);
	insertAsLC(13,lpq1->root);
	insertAsRC(12,lpq1->root);
	insertAsLC(6,lpq1->root->lc);

	insertLeftHeap(15,lpq2);
	insertAsLC(10,lpq2->root);
	insertAsRC(8,lpq2->root);
	travIn_R(lpq1->root);	   
	printf("\n");
	travIn_R(lpq2->root);	 
	lpq3->root = mergeLeftHeap(lpq1->root,lpq2->root);
	printf("\n root : %d \n" , lpq3->root->data);
	travIn_R(lpq3->root);	 
	return 0;
}