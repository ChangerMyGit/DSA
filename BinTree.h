/**
   树形结构 半线性结构
   默认为使用二叉搜索树
**/
#ifndef _TREE_H
#define _TREE_H
#include "List.h"
#include "Stack.h"
#include "Queue.h"

typedef enum { RED,BLACK } Color; 

typedef struct _binNode{
	ElemType data;
	struct _binNode * parent;
	struct _binNode * lc;
	struct _binNode * rc;
	int height;
	Color color;
} BinNode;

typedef struct _tree {
	int size;
	BinNode * root;
	BinNode * _hot;
} BinTree;

// 返回节点高度 空树为-1
#define stature(p) ((p) ? p->height : -1)
#define MAX(A , B) ( (A) > (B)  ? (A) : (B) )

/******************************
* BinNode状态与性质的判断
******************************/

#define IsRoot(x) ( ! ( (x)->parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( (x) == (x)->parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( (x) == (x)->parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x)->lc )
#define HasRChild(x) ( (x)->rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define IsLeaf(x) ( ! HasChild(x) )
/*来自父亲的引用*/
#define FromParentTo(x , y) ( IsRoot(x) ? y->root : ( IsLChild(x) ? (x)->parent->lc : (x)->parent->rc ) )
// 在左，右孩子中取更高者 等高 与父亲同侧者
#define tallerChild(x) ( stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /* 左高*/stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : (  /*右高*/ IsLChild( (x) ) ? (x)->lc : (x)->rc)))

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
//binNode作为parent的左孩子（原无）插入
BinNode * insertAsLCC(BinNode * parent , BinNode * binNode);
//binNode作为parent的右孩子（原无）插入
BinNode * insertAsRCC(BinNode * parent , BinNode * binNode);
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
// 层次遍历 使用队列
void traveLevel(BinNode * binNode);
// 获取树中所有的叶子节点数目
int getLeafNum(BinNode * binNode);
// 获取树的高度 递归实现 
int get_tree_height(BinNode * binNode);
// 平衡搜索树的查找
BinNode * searchIn(BinNode * binNode , ElemType e);
// 查找并且赋值父节点指针
BinNode * searchAndSetParent(BinNode * binNode , ElemType e , BinNode * parent);
// 查找符合条件节点的父节点
BinNode * searchParent(BinTree * tree , ElemType e);
// 插入节点
BinNode * insertNode(BinTree * binTree , ElemType x);
// 查找最大值
BinNode * getMax(BinNode * binNode);
// 查找最小值
BinNode * getMin(BinNode * binNode);
// 删除节点
void deleteBinNode(BinTree * binTree , ElemType x);
BinNode * deleteNode(BinNode * node , BinTree * binTree);
/**
  AVL 平衡二叉树的插入删除
  插入操作O（1）的复杂度 删除操作最坏可能是O（logn）的复杂度
**/
/*
BinNode * insertNodeAVL(ElemType e , BinTree * binTree);
void deleteNodeAVL(BinTree * binTree , ElemType x);
// 针对AVL 的 单旋转或者 双旋转使用3+4的重构方法实现
BinNode * connect34(BinNode * a , BinNode * b , BinNode * c,
	BinNode * T0 , BinNode * T1 , BinNode * T2 , BinNode * T3);

// 旋转使用3+4 重构
BinNode * rotateAt(BinNode * v); */
#endif