#include "PQ.h"
#include <stdlib.h>
#define  InHeap(n, i) ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  Parent(i) ( ( i - 1 ) >> 1 ) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  LChild(i) ( 1 + ( ( i ) << 1 ) ) //PQ[i]的左孩子
#define  RChild(i) ( ( 1 + ( i ) ) << 1 ) //PQ[i]的右孩子
#define  ParentValid(i) ( 0 < i ) //判断PQ[i]是否有父亲
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  LastInternal(n)   Parent( n - 1 ) //最后一个内部节点（即末节点的父亲)

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
	// 下溢
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

/*父子（至多）三者中的大者*/ 
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

// 构造优先队列
void heapify(int n , PQ_ComplHeap * pq){
	// 使用下滤方式性能更好
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