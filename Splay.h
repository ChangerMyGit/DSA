#ifndef _SPLAY_H
#define _SPLAY_H

#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "BinTree.h"

// 伸展
BinNode * splay(BinNode * v);
// 伸展树的查找
BinNode * searchSplay(BinTree * tree , ElemType e);
// 伸展树的插入
BinNode * insertSplay(BinTree * tree , ElemType e);
// 伸展树的删除
void deleteSplay(BinTree * tree , ElemType e);
#endif