#include "PQ.h"
#include <stdlib.h>
#define  InHeap(n, i) ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //�ж�PQ[i]�Ƿ�Ϸ�
#define  Parent(i) ( ( i - 1 ) >> 1 ) //PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
#define  LChild(i) ( 1 + ( ( i ) << 1 ) ) //PQ[i]������
#define  RChild(i) ( ( 1 + ( i ) ) << 1 ) //PQ[i]���Һ���
#define  ParentValid(i) ( 0 < i ) //�ж�PQ[i]�Ƿ��и���
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //�ж�PQ[i]�Ƿ���һ�����󣩺���
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //�ж�PQ[i]�Ƿ�����������

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
		// ���ڸ�Ԫ��
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
		// ���ڸ�Ԫ��
		if(e > getElem(pq->vector,Parent(n))){
			pq->vector->elem[n] = pq->vector->elem[Parent(n)];
			n = Parent(n);
		} else 
			break;
	}
	pq->vector->elem[n] = e;
}