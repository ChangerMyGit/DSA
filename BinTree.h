/**
   ���νṹ �����Խṹ
   Ĭ��Ϊʹ�ö���������
**/
#ifndef _TREE_H
#define _TREE_H
#include "List.h"
#include "Stack.h"
#include "Queue.h"
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
// ������� �ݹ�ʵ��
void travPre(BinNode * binNode);
// ����ʵ��������� ʹ��ջ
void travPre_I1(BinNode * binNode);
// �������ʹ��ջ �ڶ���ʵ�ַ�ʽ
void travPre_I2(BinNode * binNode);
//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ���������������
void visitAlongLeftBranch(BinNode * binNode , Stack * stack);
// ����ʵ���������
void travIn_R(BinNode * binNode);
//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
void goAlongLeftBranch(BinNode * binNode , Stack * stack);
//��������������㷨��������#1��
void travIn_I1(BinNode * binNode);
// ��α��� ʹ�ö���
void traveLevel(BinNode * binNode);
// ��ȡ�������е�Ҷ�ӽڵ���Ŀ
int getLeafNum(BinNode * binNode);
// ��ȡ���ĸ߶� �ݹ�ʵ�� 
int get_tree_height(BinNode * binNode);
// ƽ���������Ĳ���
BinNode * searchIn(BinNode * binNode , ElemType e);
// ���ҷ��������ڵ�ĸ��ڵ�
BinNode * searchParent(BinTree * tree , ElemType e);
// ����ڵ�
BinNode * insertNode(BinTree * binTree , ElemType x);
// �������ֵ
BinNode * getMax(BinNode * binNode);
// ������Сֵ
BinNode * getMin(BinNode * binNode);
// ɾ���ڵ�
void deleteBinNode(BinTree * binTree , ElemType x);
void deleteNode(BinNode * node);
/**
  AVL ƽ��������Ĳ���ɾ��
  �������O��1���ĸ��Ӷ� ɾ�������������O��logn���ĸ��Ӷ�
**/
BinNode * insertNodeAVL(ElemType e , BinTree * binTree);
void deleteNodeAVL(BinTree * binTree , ElemType x);
// ���AVL �� ����ת���� ˫��תʹ��3+4���ع�����ʵ��
BinNode * connect34(BinNode * a , BinNode * b , BinNode * c,
	BinNode * T0 , BinNode * T1 , BinNode * T2 , BinNode * T3);

// ��תʹ��3+4 �ع�
BinNode * rotateAt(BinNode * v);

PrintNodeAtLevel(BinNode * v , int level);
#endif