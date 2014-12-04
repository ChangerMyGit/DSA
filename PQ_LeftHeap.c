#include "PQ_LeftHeap.h"
#include <stdlib.h>
#include <stdio.h>

LeftHeap * initLeftHeap(){
	LeftHeap * heap = (LeftHeap *)malloc(sizeof(LeftHeap));
	heap->root = NULL;
	heap->size = 0;
	return heap;
}

BinNode * mergeLeftHeap(BinNode * a , BinNode * b){
	if(!a) return b;
	if(!b) return a;
	if(a->data < b->data)
		swip_Node(&a,&b); // 保证b不大于a
	a->rc = mergeLeftHeap(a->rc , b); // 将a的右子堆与b合并
	a->rc->parent = a;// 更新新父子关系
	if(!a->lc || a->lc->npl < a->rc->npl)
		swip_Node(&a->lc , &a->rc); // 保持左式堆特性
	a->npl = a->rc ? a->rc->npl + 1 : 1;//更新a的npl
	return a;
}

void insertLeftHeap(ElemType e , LeftHeap * heap){
	BinNode * newNode = newBinNode(e,NULL);
	heap->root = mergeLeftHeap(heap->root , newNode);
	heap->root->parent = NULL;
	heap->size++;
}

ElemType delMaxLeftHeap(LeftHeap * heap){
	BinNode * lc = heap->root->lc;//左子堆
	BinNode * rc = heap->root->rc;//右子堆
	heap->root = mergeLeftHeap(lc,rc);
	if(heap->root) 
		heap->root->parent = NULL;
}

// 节点交换 交换指针引用
void swip_Node(BinNode ** a , BinNode ** b){
	BinNode * temp = *a;
	*a = (*b);
	*b = temp;
}