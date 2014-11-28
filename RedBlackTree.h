#ifndef _RBTREE_H
#define _RBTREE_H
#include "AVLTree.h"

#define IsBlack(x) ( (x)->color == BLACK || !(x))
#define IsRed(x) ((x)->color == RED)

void insertRBTree(ElemType x ,BinTree * tree);
// ���˫������
void solveDoubleRed(BinNode * binNode ,BinTree * tree);
//��ȡ�����常�ڵ�
BinNode * getUncle(BinNode * binNode);
#endif