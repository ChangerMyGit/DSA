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
} PQ_ComplHeap; 


PQ_ComplHeap * initPQ(int size);

// ���ձȽ���ȷ�������ȼ�����������
void insertPQ(Elem e , PQ_ComplHeap * pq);
// ȡ�����ȼ���ߵĴ���
Elem getMax(PQ_ComplHeap * pq);
// ɾ�����ȼ���ߵĴ���
Elem delMax(PQ_ComplHeap * pq);
// ����
void percolateUp(int n , PQ_ComplHeap * pq);
#endif