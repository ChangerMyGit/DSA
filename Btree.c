#include "Btree.h"
#include <stdlib.h>
#include <memory.h>

BTree * initBtree(int order){
    BTree * tree = (BTree *)malloc(sizeof(BTree));
	tree->root = NULL;
	tree->hot = NULL;
	tree->size = 0;
	tree->_order = order;
}

BTNode * newBTNode(BTNode * parent , int order ,int keys_Length){
	BTNode * node = (BTNode *)malloc(sizeof(BTNode));
	node->parent = parent;
	// 至多M个孩子
	node->child = initVector(order * sizeof(BTNode *));
	// 至多M-1个关键码
	node->keys = initVector(keys_Length);
	return node;
}

BTNode * searchBtree(Elem e , BTree * tree){
	int r;
	BTNode * v  = tree->root;
	BTNode * hot = NULL;
	while(v){
		r = searchInChild(e,v->keys);
		if(v->keys->elem[r] == e) 
			return v; // 返回节点
		hot = v; 
		v = (BTNode *)v->child->elem[r+1];
	}
	return NULL;
}

int searchInChild(Elem e , Vector * keys){
	int lo = 0;
	int hi = keys->size;
	int r = binSearchInChild(keys,lo,hi,e);
	return r;
}

int binSearchInChild(Vector * keys,int lo , int hi,int key){
	int mi;
	if(hi == 0) return -1;
	else if(lo == hi) return lo -1;
	else if(lo < hi){
		mi = (lo + hi) >> 1;
		if(keys->elem[mi] == key) return mi;
		else if(keys->elem[mi] > key) return binSearchInChild(keys,lo,mi,key);
		else if(keys->elem[mi] < key) return binSearchInChild(keys,mi+1,hi,key);
	}
	return lo;
}