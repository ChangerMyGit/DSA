#ifndef _RBTREE_H
#define _RBTREE_H
#include "AVLTree.h"

#define IsBlack(x) ( (x)->color == BLACK || !(x))
#define IsRed(x) ((x)->color == RED)

void insertRBTree(ElemType x ,BinTree * tree);
// 解决双红问题
void solveDoubleRed(BinNode * binNode ,BinTree * tree);
//获取数的叔父节点
BinNode * getUncle(BinNode * binNode);
#endif