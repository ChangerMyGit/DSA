#ifndef _RBTREE_H
#define _RBTREE_H
#include "AVLTree.h"

#define IsBlack(x) ( !x || (x)->color == BLACK )
#define IsRed(x) (x && (x)->color == RED)

void insertRBTree(ElemType x ,BinTree * tree);
// 解决双红问题
void solveDoubleRed(BinNode * binNode ,BinTree * tree);
//获取数的叔父节点
BinNode * getUncle(BinNode * binNode);
// 红黑树删除
void removeRBTree(ElemType x ,BinTree * tree);
// 解决双黑问题
void solveDoubleBlack(BinNode * r ,BinTree * tree);

#endif