#ifndef  _BTREE_H
#define _BTREE_H

#include "Vector.h"

typedef struct _btreeNode{
	struct _btreeNode * parent ; //���ڵ�
	Vector * keys;   //�ؼ������� ��������
	Vector * child; //�����������䳤���ܱ�key��һ��
} BTNode;

// B-��
typedef struct _btree{
	int size;//�ؼ�������
	int _order; // ����
	BTNode * root;// ��
	BTNode * hot;// search �����ʵķǿսڵ���
} BTree;

// ��ʼ��B��
BTree * initBtree(int order);
// �����µ�B���ڵ�
BTNode * newBTNode(BTNode * parent , int order, int keys_Length);
// ��ѯ�ڵ�
BTNode * searchBtree(Elem e , BTree * tree);
void insertBtree(Elem e);
void removeBtree(Elem e);
// ����������ķ��Ѵ���
void solveOverflow(BTNode * btNode);
// ��ɾ��������ĺϲ�����
void solveUnderflow(BTNode * btNode);
//����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����
int searchInChild(Elem e , Vector * keys);
// ���ֲ��� ����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����
int binSearchInChild(Vector * keys,int lo , int hi,int key);
#endif