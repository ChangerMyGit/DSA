#include "PQ.h"
#include <stdlib.h>
#define  InHeap(n, i) ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  Parent(i) ( ( i - 1 ) >> 1 ) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  LChild(i) ( 1 + ( ( i ) << 1 ) ) //PQ[i]的左孩子
#define  RChild(i) ( ( 1 + ( i ) ) << 1 ) //PQ[i]的右孩子
#define  ParentValid(i) ( 0 < i ) //判断PQ[i]是否有父亲
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子

PQ_ComplHeap * initPQ(int size){
	PQ_ComplHeap * pq = (PQ_ComplHeap *)malloc(sizeof(PQ_ComplHeap));
	pq->vector = initVector(size);
	return pq;
}

void insertPQ(Elem e , PQ_ComplHeap * pq){
	int n;
	insert(pq->vector,e);
	n = pq->vector->size -1;
	percolateUp(n,pq);
}

void insertPQ2(Elem e , PQ_ComplHeap * pq){
	int n;
	insert(pq->vector,e);
	n = pq->vector->size -1;
	percolateUp2(n,pq);
}
void percolateUp(int n , PQ_ComplHeap * pq){
	while(ParentValid(n)){
		// 大于父元素
		if(getElem(pq->vector,n) > getElem(pq->vector,Parent(n))){
			vec_swap(&pq->vector->elem[Parent(n)],&pq->vector->elem[n]);
			n = Parent(n);
		}
		else 
			break;
	}
}

void percolateUp2(int n , PQ_ComplHeap * pq){
	Elem e = getElem(pq->vector,n);
	while(ParentValid(n)){
		// 大于父元素
		if(e > getElem(pq->vector,Parent(n))){
			pq->vector->elem[n] = pq->vector->elem[Parent(n)];
			n = Parent(n);
		} else 
			break;
	}
	pq->vector->elem[n] = e;
}