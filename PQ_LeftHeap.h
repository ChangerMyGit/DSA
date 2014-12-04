#ifndef _LEFTHEAP_H
#define _LEFTHEAP_H
#include "BinTree.h"
// 左式堆 不再使用数组的方式表示 使用二叉树的方式表示 堆得结构左倾
/**
   左式堆的结点相比于一般的堆来说，增加了Npl属性，Npl是 null path length 的缩写，
   指的是从该结点到达一个没有两个孩子的结点的最短距离（一个孩子的结点或者叶子）。
   一般定义NULL的Npl为-1以使计算简便。容易得到，
   任意结点的Npl是它的孩子的Npl中较小的那个结点的Npl+1.
**/
typedef struct _left_heap {
	BinNode * root; 
	int size;
} LeftHeap;


LeftHeap * initLeftHeap();
// 插入
void insertLeftHeap(ElemType e , LeftHeap * heap);
// 堆合并
BinNode * mergeLeftHeap(BinNode * a , BinNode * b);

ElemType delMaxLeftHeap(LeftHeap * heap);

ElemType getMaxLeftHeap(LeftHeap * heap);

void swip_Node(BinNode ** a , BinNode ** b);
#endif