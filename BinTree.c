#include "BinTree.h"
#include <stdlib.h>
#include <stdio.h>

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
	return node;
}

BinNode * insertAsLC(ElemType e , BinNode * binNode){
	BinNode * newNode = newBinNode(e,binNode);
	binNode->lc = newNode;
	return newNode;
}

BinNode * insertAsRC(ElemType e , BinNode * binNode){
	BinNode * newNode = newBinNode(e,binNode);
	binNode->rc = newNode;
	return newNode;
}

BinNode * root(BinTree * binTree){
	return binTree->root;
}