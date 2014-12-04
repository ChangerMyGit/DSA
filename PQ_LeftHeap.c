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
		swip_Node(&a,&b); // ��֤b������a
	a->rc = mergeLeftHeap(a->rc , b); // ��a�����Ӷ���b�ϲ�
	a->rc->parent = a;// �����¸��ӹ�ϵ
	if(!a->lc || a->lc->npl < a->rc->npl)
		swip_Node(&a->lc , &a->rc); // ������ʽ������
	a->npl = a->rc ? a->rc->npl + 1 : 1;//����a��npl
	return a;
}

void insertLeftHeap(ElemType e , LeftHeap * heap){
	BinNode * newNode = newBinNode(e,NULL);
	heap->root = mergeLeftHeap(heap->root , newNode);
	heap->root->parent = NULL;
	heap->size++;
}

ElemType delMaxLeftHeap(LeftHeap * heap){
	BinNode * lc = heap->root->lc;//���Ӷ�
	BinNode * rc = heap->root->rc;//���Ӷ�
	heap->root = mergeLeftHeap(lc,rc);
	if(heap->root) 
		heap->root->parent = NULL;
}

// �ڵ㽻�� ����ָ������
void swip_Node(BinNode ** a , BinNode ** b){
	BinNode * temp = *a;
	*a = (*b);
	*b = temp;
}