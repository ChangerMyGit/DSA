//���ȶ���
/**
ʹ����ȫ�����ʵ��
����������֣����Ѻ���С�ѡ�
���ѣ������ļ�ֵ���Ǵ��ڻ�����κ�һ���ӽڵ�ļ�ֵ��
��С�ѣ������ļ�ֵ����С�ڻ�����κ�һ���ӽڵ�ļ�ֵ��
**/
#ifndef _PQ_H
#define _PQ_H
#include "Vector.h"

typedef struct _pq{
	Vector * vector;
	int size;
} PQ_ComplHeap; 


PQ_ComplHeap * initPQ(int size);

// ���ձȽ���ȷ�������ȼ�����������
void insertPQ(Elem e , PQ_ComplHeap * pq);
void insertPQ2(Elem e , PQ_ComplHeap * pq);
// ȡ�����ȼ���ߵĴ���
Elem getMaxPQ(PQ_ComplHeap * pq);
// ɾ�����ȼ���ߵĴ���
Elem delMax(PQ_ComplHeap * pq);
// ����
void percolateUp(int n , PQ_ComplHeap * pq);
void percolateUp2(int n , PQ_ComplHeap * pq);
// ����
void percolateDown(int n , PQ_ComplHeap * pq);
/*���ӣ����ࣩ�����еĴ���*/ 
int ProperParent(int n , PQ_ComplHeap * pq);
// �������ȶ��� �� ������ �� ʹ������
void heapify(int n , PQ_ComplHeap * pq);
// ������
void heapSort(PQ_ComplHeap * pq);
#endif