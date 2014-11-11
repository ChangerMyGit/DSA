#include "BinTree.h"
#include "Stack.h"
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

void updateHeightAbove(BinNode *     binNode){
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

// 递归实现
void travPre(BinNode * binNode){
	if(binNode){
		printf(" %c ",binNode->data);
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
		// 先入右子树 再入左子树 栈是先进后出
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
		// 打印所有的左节点
		visitAlongLeftBranch(binNode,stack);
		// 依次处理所有的右子数 使用栈逆序处理
		if(empty(stack)) 
			break;
		binNode = pop(stack);
	}
	free(stack);
}

void travIn_R(BinNode * binNode){
	if(!binNode) return;
	travIn_R(binNode->lc);
	printf(" %c ",binNode->data);
	travIn_R(binNode->rc);
}

//从当前节点出发，沿左分支不断深入，直至没有左分支的节点
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
	// 入队根节点
	enqueue(binNode,queue);
	while(!emptyQueue(queue)){
	   binNode = dequeue(queue);
	   printf(" %c ",binNode->data);
	   if(binNode->lc) enqueue(binNode->lc,queue);
	   if(binNode->rc) enqueue(binNode->rc,queue);
	}
	free(queue);
}

// 递归求解
int getLeafNum(BinNode * binNode){
   if(binNode == NULL) return 0;
   if(binNode->lc == NULL && binNode->rc == NULL)
	   return 1;
   return getLeafNum(binNode->lc) + getLeafNum(binNode->rc);
}

int get_tree_height(BinNode * binNode){
   if(!binNode) return -1; // 空结点
   if(binNode->lc == NULL && binNode->rc == NULL)
	   return 0; // 叶子节点
   return MAX(get_tree_height(binNode->lc),get_tree_height(binNode->rc)) + 1;
}