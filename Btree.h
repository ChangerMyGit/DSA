#ifndef  _BTREE_H
#define _BTREE_H

#include "Vector.h"

typedef struct _btreeNode{
	struct _btreeNode * parent ; //父节点
	Vector * keys;   //关键码向量 有序向量
	Vector * child; //孩子向量（其长度总比key多一）
} BTNode;

// B-树
typedef struct _btree{
	int size;//关键码总数
	int _order; // 阶数
	BTNode * root;// 根
	BTNode * hot;// search 最后访问的非空节点数
} BTree;

// 初始化B树
BTree * initBtree(int order);
// 构造新的B树节点
BTNode * newBTNode(BTNode * parent , int order, int keys_Length);
// 查询节点
BTNode * searchBtree(Elem e , BTree * tree);
void insertBtree(Elem e);
void removeBtree(Elem e);
// 因插入而上溢的分裂处理
void solveOverflow(BTNode * btNode);
// 因删除而下溢的合并处理
void solveUnderflow(BTNode * btNode);
//在有序向量的区间[lo, hi)内，确定不大于e的最后一个节点的秩
int searchInChild(Elem e , Vector * keys);
// 二分查找 在有序向量的区间[lo, hi)内，确定不大于e的最后一个节点的秩
int binSearchInChild(Vector * keys,int lo , int hi,int key);
#endif