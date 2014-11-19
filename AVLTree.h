#ifndef _AVL_H
#define _AVL_H

#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "BinTree.h"

// AVL ƽ������
// ����ƽ��
#define Banlance(x) ( stature((x)->lc) == stature((x)->rc) )
// ƽ������
#define BalFac(x) ( stature((x)->lc) - stature((x)->rc) )
// ƽ������
#define AvlBanlance(x) ( ( BalFac(x) > -2 ) && ( BalFac(x) < 2 ) )

/**
  AVL ƽ��������Ĳ���ɾ��
  �������O��1���ĸ��Ӷ� ɾ�������������O��logn���ĸ��Ӷ�
**/
BinNode * insertNodeAVL(ElemType e , BinTree * binTree);
void deleteNodeAVL(BinTree * binTree , ElemType x);
// ���AVL �� ����ת���� ˫��תʹ��3+4���ع�����ʵ��
BinNode * connect34(BinNode * a , BinNode * b , BinNode * c,
	BinNode * T0 , BinNode * T1 , BinNode * T2 , BinNode * T3);

// ��תʹ��3+4 �ع�
BinNode * rotateAt(BinNode * v);

#endif