#include "BinTree.h"
#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>

// ���ؽڵ�߶� ����Ϊ-1
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
	// �ڵ�ĸ߶ȵ������������������������߶� + 1
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
	// ��������-1��
	return -1;
}

// �ݹ�ʵ��
void travPre(BinNode * binNode){
	if(binNode){
		printf(" %d ",binNode->data);
		travPre(binNode->lc);
		travPre(binNode->rc);
	}
}

void travPre_I1(BinNode * binNode){
	Stack * stack = initStack();
	push(binNode,stack);
	while(!empty(stack)){
		binNode = pop(stack);
		printf(" %c ",binNode->data);
		// ���������� ���������� ջ���Ƚ����
		if(binNode->rc)  push(binNode->rc,stack);
		if(binNode->lc)  push(binNode->lc,stack);
	}
	free(stack);
}

void visitAlongLeftBranch(BinNode * binNode , Stack * stack){
	while(binNode){
		printf(" %c ",binNode->data);
		push(binNode->rc,stack);
		binNode = binNode->lc;
	}
}

void travPre_I2(BinNode * binNode){
	Stack * stack = initStack();
	while(TRUE){
		// ��ӡ���е���ڵ�
		visitAlongLeftBranch(binNode,stack);
		// ���δ������е������� ʹ��ջ������
		if(empty(stack)) 
			break;
		binNode = pop(stack);
	}
	free(stack);
}

void travIn_R(BinNode * binNode){
	if(!binNode) return;
	travIn_R(binNode->lc);
	printf(" %d ",binNode->data);
	travIn_R(binNode->rc);
}

//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
void goAlongLeftBranch(BinNode * binNode , Stack * stack){
	while(binNode){
		push(binNode,stack);
		binNode = binNode->lc;
	}
}

void travIn_I1(BinNode * binNode){
	Stack * stack = initStack();
	while(TRUE){
		goAlongLeftBranch(binNode,stack);
		if(empty(stack)) 
			break;
		binNode = pop(stack);
		printf(" %c ",binNode->data);
		binNode = binNode->rc;
	}
	free(stack);
}

void traveLevel(BinNode * binNode){
	Queue * queue = initQueue();
	// ��Ӹ��ڵ�
	enqueue(binNode,queue);
	while(!emptyQueue(queue)){
		binNode = dequeue(queue);
		printf(" %c ",binNode->data);
		if(binNode->lc) enqueue(binNode->lc,queue);
		if(binNode->rc) enqueue(binNode->rc,queue);
	}
	free(queue);
}

// �ݹ����
int getLeafNum(BinNode * binNode){
	if(binNode == NULL) return 0;
	if(binNode->lc == NULL && binNode->rc == NULL)
		return 1;
	return getLeafNum(binNode->lc) + getLeafNum(binNode->rc);
}

int get_tree_height(BinNode * binNode){
	if(!binNode) return -1; // �ս��
	if(binNode->lc == NULL && binNode->rc == NULL)
		return 0; // Ҷ�ӽڵ�
	return MAX(get_tree_height(binNode->lc),get_tree_height(binNode->rc)) + 1;
}

BinNode * searchIn(BinNode * binNode , ElemType e){
	if(binNode){
		if(binNode->data == e)
			return binNode;
		else if(binNode->data > e)
			return searchIn(binNode->lc,e);
		else if(binNode->data < e)
			return searchIn(binNode->rc,e);
	}
	return NULL;
}

BinNode * searchParent(BinTree * tree , ElemType e){
	BinNode * parent = NULL;
	BinNode * node = root(tree);
	while(node){
		if(node->data > e)
			node = node->lc;
		else if(node->data < e)
			node = node->rc;
		else if(node->data == e)
			break;
		parent = node;
	}
	return parent;
}

void insertNode(BinTree * binTree , ElemType x){
	BinNode * newNode, * parent = NULL, * binNode = root(binTree);
	if(binNode == NULL) {
		insertAsRoot(binTree , x);
		return;
	}
	while(binNode){
		parent = binNode;
		if(binNode->data == x)
			break ;
		else if(binNode->data > x)
			binNode = binNode->lc;
		else if(binNode->data < x)
			binNode = binNode->rc;
	}

	if(binNode == NULL){
		newNode = newBinNode(x,parent);
		if(parent->data > x)
			insertAsLC(x,parent);
		else if(parent->data < x)
			insertAsRC(x,parent);
		binTree->size++;
	}
}

BinNode * getMax(BinNode * binNode){
	if(binNode == NULL) return NULL;
	while(binNode->rc)
		binNode = binNode->rc;
	return binNode;
}

BinNode * getMin(BinNode * binNode){
	while(binNode->lc)
		binNode = binNode->lc;
	return binNode;
}

void deleteNode(BinNode * node){
	ElemType e;
	BinNode * child , * parent = node->parent;
	if((node->lc && !node->rc) || (!node->lc && node->rc)){
		child = (node->lc) ? node->lc : node->rc;
		node->data = child->data;
		node->height = child->height;
		free(child);
		if(node->lc)
			node->lc = NULL; 
		else 
			node->rc = NULL;
	}
	// Ҷ�ӽڵ�
	else if(!node->lc && !node->rc){
		if(parent->lc == node)
			parent->lc = NULL;
		else 
			parent->rc = NULL;
		free(node);
	} 
	else if(node->lc && node->rc){
		// �ҵ�ɾ��Ԫ�ص���С���
		// ���Ȼ���Ԫ�أ�Ȼ���滻
		child = getMin(node->rc);
		e = child->data;
		child->data = node->data;
		node->data = e;
		deleteNode(child);
	}
}

// ɾ���ڵ�
void deleteBinNode(BinTree * binTree , ElemType x){
	BinNode * parent;
	BinNode * node = searchIn(root(binTree),x);
	if(node){
		parent = node->parent;
		deleteNode(node);
		binTree->size--;
		updateHeightAbove(parent);
	}
}

