#include "BinTree.h"
#include <stdlib.h>
#include <stdio.h>

// 返回节点高度 空树为-1
#define stature(p) ((p) ? p->height : -1)
#define MAX(A , B) ( (A) > (B)  ? (A) : (B) )

BinTree * initBinTree(){
	BinTree * tree = (BinTree *)malloc(sizeof(BinTree));
	tree->root = NULL;
	tree->size = 0;
	return tree;
}

BinNode * insertAsRoot(BinTree * binTree, ElemType x){
	BinNode * root = newBinNode(x,NULL);
	binTree->root = root;
	binTree->size++;
	return root;
}

BinNode * newBinNode(ElemType x , BinNode * parent){
	BinNode * node = (BinNode *)malloc(sizeof(BinNode));
	node->data = x;
	node->parent = parent;
	node->height = 0;
	node->lc = NULL;
	node->rc = NULL;
	return node;
}

BinNode * insertAsLC(ElemType e , BinNode * binNode){
	BinNode * newNode = newBinNode(e,binNode);
	binNode->lc = newNode;
	updateHeightAbove(binNode);
	return newNode;
}

BinNode * insertAsRC(ElemType e , BinNode * binNode){
	BinNode * newNode = newBinNode(e,binNode);
	binNode->rc = newNode;
	updateHeightAbove(binNode);
	return newNode;
}

BinNode * root(BinTree * binTree){
	return binTree->root;
}

int getBinNodeSize(BinNode * binNode){
   int size = 1;
   if(binNode->lc) size += getBinNodeSize(binNode->lc);
   if(binNode->rc) size += getBinNodeSize(binNode->rc);
   return size;
}

void updateHeight(BinNode * binNode){
	// 节点的高度等于左子树或者右子树的最大高度 + 1
	binNode->height = 1 + MAX(stature(binNode->lc),stature(binNode->rc));
}

void updateHeightAbove(BinNode * binNode){
	while(binNode){
		updateHeight(binNode);
		binNode = binNode->parent;
	}
}

int getTreeHeight(BinTree * binTree){
	if(binTree->root){
		return binTree->root->height;
	}
	// 空树返回-1；
	return -1;
}