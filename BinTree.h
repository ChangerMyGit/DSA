/**
   树形结构 半线性结构
**/
#ifndef _TREE_H
#define _TREE_H
#include "List.h"
#include "Stack.h"
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
// 先序遍历 递归实现
void travPre(BinNode * binNode);
// 迭代实现先序遍历 使用栈
void travPre_I1(BinNode * binNode);
// 先序遍历使用栈 第二种实现方式
void travPre_I2(BinNode * binNode);
//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
void visitAlongLeftBranch(BinNode * binNode , Stack * stack);
// 迭代实现中序遍历
void travIn_R(BinNode * binNode);
//从当前节点出发，沿左分支不断深入，直至没有左分支的节点
void goAlongLeftBranch(BinNode * binNode , Stack * stack);
//二叉树中序遍历算法（迭代版#1）
void travIn_I1(BinNode * binNode);
#endif