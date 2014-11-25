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
	// ����M������
	node->child = initVector(order * sizeof(BTNode *));
	// ����M-1���ؼ���
	node->keys = initVector(keys_Length);
    setAllValue(node->child,NULL,order);
	setAllValue(node->keys,NULL,order-1);
	return node;
}

BTNode * searchBtree(Elem e , BTree * tree){
	int r;
	BTNode * v  = tree->root;
	BTNode * hot = NULL;
	while(v){
		r = searchInChild(e,v->keys);
		if(v->keys->elem[r] == e) 
			return v; // ���ؽڵ�
		hot = v; 
		tree->hot = hot;
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

void solveOverflow(BTNode * btNode,BTree * tree){
	BTNode * u;
	int s;
	if (tree->_order >= btNode->child->size) 
		return; //�ݹ������ǰ�ڵ㲢δ����
	//��㣨��ʱӦ��_order = key.size() = child.size() - 1��
	s = tree->_order/2;
	//u = newBTNode(NULL,);
}

void insertBtree(Elem e , BTree * tree){
	int r;
	BTNode * hot;
	BTNode * node = searchBtree(e,tree);
	hot = tree->hot;
	if(node) 
		return; // ������ڲ���ʧ��
	if(!hot) {
		// �������ȹ���һ�����ڵ�
		tree->root = newBTNode(NULL,tree->_order,(tree->_order - 1) * sizeof(int));
		insert(tree->root->keys,e);
		insert(tree->root->child,NULL);
		return;
	}

	r = searchInChild(e,hot->keys);//�ڽڵ�_hot������ؼ��������в��Һ��ʵĲ���λ��
	insert2(hot->keys,e,r+1); //���¹ؼ��������Ӧ��λ��
	insert2(hot->child,NULL,r+2);
	tree->size++;//����ȫ����ģ
	solveOverflow(hot,tree); //���б�Ҫ����������
}