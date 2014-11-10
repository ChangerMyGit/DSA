/**
   ���νṹ �����Խṹ
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

// ��������ʼ��
BinTree * initBinTree();
// �����µ����ڵ�
BinNode * newBinNode(ElemType x , BinNode * parent);
//������ڵ�
BinNode * insertAsRoot(BinTree * binTree , ElemType x);
//e��Ϊx�����ӣ�ԭ�ޣ�����
BinNode * insertAsLC(ElemType e , BinNode * binNode);
//e��Ϊx���Һ��ӣ�ԭ�ޣ�����
BinNode * insertAsRC(ElemType e , BinNode * binNode);
// ��ø��ڵ�
BinNode * root(BinTree * binTree);
// ���ĳһ�����Ĺ�ģ ���е�Ԫ����Ŀ
int getBinNodeSize(BinNode * binNode);
// �������ĸ߶�
void updateHeight(BinNode * binNode);
//��bnNode������������������
void updateHeightAbove(BinNode * binNode);
// ��ȡ���ĸ߶�
int getTreeHeight(BinTree * binTree);
#endif