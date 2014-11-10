/**
   树形结构 半线性结构
**/
#ifndef _TREE_H
#define _TREE_H
#include "List.h"
typedef struct _binNode{
	ElemType data;
	struct _binNode * parent;
	struct _binNode * lc;
	struct _binNode * rc;
	int height;
} BinNode;

typedef struct _tree {
	int size;
	BinNode * root;
} BinTree;

// 二叉树初始化
BinTree * initBinTree();
// 构建新的树节点
BinNode * newBinNode(ElemType x , BinNode * parent);
//插入根节点
BinNode * insertAsRoot(BinTree * binTree , ElemType x);
//e作为x的左孩子（原无）插入
BinNode * insertAsLC(ElemType e , BinNode * binNode);
//e作为x的右孩子（原无）插入
BinNode * insertAsRC(ElemType e , BinNode * binNode);
// 获得根节点
BinNode * root(BinTree * binTree);
// 获得某一个数的规模 所有的元素数目
int getBinNodeSize(BinNode * binNode);
// 更新数的高度
void updateHeight(BinNode * binNode);
//从bnNode出发，覆盖历代祖先
void updateHeightAbove(BinNode * binNode);
// 获取数的高度
int getTreeHeight(BinTree * binTree);
#endif