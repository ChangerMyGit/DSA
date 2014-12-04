#ifndef _LEFTHEAP_H
#define _LEFTHEAP_H
#include "BinTree.h"
// ��ʽ�� ����ʹ������ķ�ʽ��ʾ ʹ�ö������ķ�ʽ��ʾ �ѵýṹ����
/**
   ��ʽ�ѵĽ�������һ��Ķ���˵��������Npl���ԣ�Npl�� null path length ����д��
   ָ���ǴӸý�㵽��һ��û���������ӵĽ�����̾��루һ�����ӵĽ�����Ҷ�ӣ���
   һ�㶨��NULL��NplΪ-1��ʹ�����㡣���׵õ���
   �������Npl�����ĺ��ӵ�Npl�н�С���Ǹ�����Npl+1.
**/
typedef struct _left_heap {
	BinNode * root; 
	int size;
} LeftHeap;


LeftHeap * initLeftHeap();
// ����
void insertLeftHeap(ElemType e , LeftHeap * heap);
// �Ѻϲ�
BinNode * mergeLeftHeap(BinNode * a , BinNode * b);

ElemType delMaxLeftHeap(LeftHeap * heap);

ElemType getMaxLeftHeap(LeftHeap * heap);

void swip_Node(BinNode ** a , BinNode ** b);
#endif