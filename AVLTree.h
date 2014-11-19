#ifndef _AVL_H
#define _AVL_H

#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "BinTree.h"

// AVL 平衡因子
// 理想平衡
#define Banlance(x) ( stature((x)->lc) == stature((x)->rc) )
// 平衡因子
#define BalFac(x) ( stature((x)->lc) - stature((x)->rc) )
// 平衡条件
#define AvlBanlance(x) ( ( BalFac(x) > -2 ) && ( BalFac(x) < 2 ) )

/**
  AVL 平衡二叉树的插入删除
  插入操作O（1）的复杂度 删除操作最坏可能是O（logn）的复杂度
**/
BinNode * insertNodeAVL(ElemType e , BinTree * binTree);
void deleteNodeAVL(BinTree * binTree , ElemType x);
// 针对AVL 的 单旋转或者 双旋转使用3+4的重构方法实现
BinNode * connect34(BinNode * a , BinNode * b , BinNode * c,
	BinNode * T0 , BinNode * T1 , BinNode * T2 , BinNode * T3);

// 旋转使用3+4 重构
BinNode * rotateAt(BinNode * v);

#endif