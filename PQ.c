#include "PQ.h"
#include <stdlib.h>
#define  InHeap(n, i) ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //�ж�PQ[i]�Ƿ�Ϸ�
#define  Parent(i) ( ( i - 1 ) >> 1 ) //PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
#define  LChild(i) ( 1 + ( ( i ) << 1 ) ) //PQ[i]������
#define  RChild(i) ( ( 1 + ( i ) ) << 1 ) //PQ[i]���Һ���
#define  ParentValid(i) ( 0 < i ) //�ж�PQ[i]�Ƿ��и���
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //�ж�PQ[i]�Ƿ���һ�����󣩺���
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //�ж�PQ[i]�Ƿ�����������
#define  LastInternal(n)   Parent( n - 1 ) //���һ���ڲ��ڵ㣨��ĩ�ڵ�ĸ���)

PQ_ComplHeap * initPQ(int size){
	PQ_ComplHeap * pq = (PQ_ComplHeap *)malloc(sizeof(PQ_ComplHeap));
	pq->vector = initVector(size);
	pq->size = 0;
	return pq;
}

void insertPQ(Elem e , PQ_ComplHeap * pq){
	int n;
	insert(pq->vector,e);
	pq->size++;
	n = pq->vector->size -1;
	percolateUp(n,pq);
}

void insertPQ2(Elem e , PQ_ComplHeap * pq){
	int n;
	insert(pq->vector,e);
	pq->size++;
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

Elem getMaxPQ(PQ_ComplHeap * pq){
	if(pq->size == 0)
		return NULL;
	return getElem(pq->vector,0);
}

Elem delMax(PQ_ComplHeap * pq){
	Elem e ;
	if(pq->size == 0)
		return;
	e = getElem(pq->vector,0);
	pq->vector->elem[0] = getElem(pq->vector,pq->size-1);
	deleteSingle(pq->vector,pq->size-1);
	pq->size--;
	// ����
	percolateDown(0,pq);
	return e;
}

void percolateDown(int n , PQ_ComplHeap * pq){
	int i;
	while(n != (i = ProperParent(n,pq))){
		vec_swap(&pq->vector->elem[n],&pq->vector->elem[i]);
		n = i;
	}
}

/*���ӣ����ࣩ�����еĴ���*/ 
int ProperParent(int n , PQ_ComplHeap * pq){
	int lc  = -1, rc = -1 ,temp;
	if(LChildValid(pq->size, n)) 
		lc = LChild(n);
	if(RChildValid(pq->size, n)) 
		rc = RChild(n);
	if(lc == -1 && rc == -1)
		return n;
	else if(lc != -1 && rc == -1)
		return (getElem(pq->vector,lc) >= getElem(pq->vector,n)) ? lc : n;
	else if(rc != -1 && lc == -1)
		return (getElem(pq->vector,rc) >= getElem(pq->vector,n)) ? rc : n;
	else if(rc != -1 && lc != -1){
		temp = (getElem(pq->vector,lc) >= getElem(pq->vector,rc)) ? lc : rc;
		return (getElem(pq->vector,temp) >= getElem(pq->vector,n)) ? temp : n;
	}
	return n;
}

// �������ȶ���
void heapify(int n , PQ_ComplHeap * pq){
	// ʹ�����˷�ʽ���ܸ���
	int i;
	for(i = 0;i<n;i++){
		insert(pq->vector,i);
		pq->size++;
	}
	for(i = LastInternal(n); i>=0 ; i--)
		percolateDown(i,pq);
}

void heapSort(PQ_ComplHeap * pq){
	Elem e ;
	int length ;
	for(length = pq->size;length > 0;length--){
		e = delMax(pq);
		insert2(pq->vector,e,length - 1);
	}
}