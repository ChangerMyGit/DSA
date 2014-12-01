#include "BinTree.h"
#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>



// AVL 平衡因子
// 理想平衡
#define Banlance(x) ( stature((x)->lc) == stature((x)->rc) )
// 平衡因子
#define BalFac(x) ( stature((x)->lc) - stature((x)->rc) )
// 平衡条件
#define AvlBanlance(x) ( ( BalFac(x) > -2 ) && ( BalFac(x) < 2 ) )

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
//( stature( (x)->lc ) > stature( (x)->rc ) ) ? (x)->lc : (x)->rc

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
	node->color = RED;
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

BinNode * insertAsLCC(BinNode * parent , BinNode * binNode){
	parent->lc = binNode;
	updateHeightAbove(parent);
	return binNode;
}

BinNode * insertAsRCC(BinNode * parent , BinNode * binNode){
	parent->rc = binNode;
	updateHeightAbove(parent);
	return binNode;
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

// 递归实现
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
	printf("Left : %d  Center : %d  Right : %d  Color : %s \n",binNode->lc ? binNode->lc->data :
		0 , binNode->data , binNode->rc ? binNode->rc->data : 0 , binNode->color == RED ? "红色" : "黑色");
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
	//if(binNode->lc == NULL && binNode->rc == NULL)
	//return 0; // 叶子节点
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

BinNode * searchAndSetParent(BinNode * binNode , ElemType e , BinNode * parent){
	while(binNode){
		if(binNode->data == e){
			*parent = *(binNode->parent);
			return binNode;
		}
		else if(binNode->data > e){
			*parent = *binNode;
			binNode = binNode->lc;
		}
		else if(binNode->data < e){
			*parent = *binNode;
			binNode = binNode->rc;
		}
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

BinNode * insertNode(BinTree * binTree , ElemType x){
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
			//insertAsLC(x,parent);
			insertAsLCC(parent,newNode);
		else if(parent->data < x)
			//insertAsRC(x,parent);
			insertAsRCC(parent,newNode);
		binTree->size++;
	}
	return newNode;
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

BinNode * deleteNode(BinNode * node, BinTree * binTree){
	ElemType e;
	BinNode * child , * parent = node->parent;
	binTree->_hot = parent;
	// 存在一个节点
	if((node->lc && !node->rc) || (!node->lc && node->rc)){
		child = (node->lc) ? node->lc : node->rc;
		child->parent = parent;
		if(!IsRoot(node)){
			if(IsLChild(node)) 
				parent->lc = child ;
			else 
				parent->rc = child;
		} else
			binTree->root = child;
		free(node);
		return child;
	}
	// 叶子节点
	else if(!node->lc && !node->rc){
		if(!IsRoot(node)){
			if(IsLChild(node))
				parent->lc = NULL;
			else
				parent->rc = NULL;
		}
		else 
			binTree->root = NULL;
		free(node);
		return NULL;
	} 
	else if(node->lc && node->rc){
		// 找到删除元素的最小后继
		// 首先互换元素，然后替换
		child = getMin(node->rc);
		e = child->data;
		child->data = node->data;
		node->data = e;
		deleteNode(child,binTree);
		return node;
	}
}

// 删除节点

void deleteBinNode(BinTree * binTree , ElemType x){
	BinNode * parent;
	BinNode * node = searchIn(root(binTree),x);
	if(node){
		parent = node->parent;
		deleteNode(node,binTree);
		binTree->size--;
		if(parent)
			updateHeightAbove(parent);		
	}
}
/*
BinNode * connect34(BinNode * a , BinNode * b , BinNode * c,
	BinNode * T0 , BinNode * T1 , BinNode * T2 , BinNode * T3){
		a->lc = T0;
		if(T0) T0->parent = a;
		a->rc = T1;
		if(T1) T1->parent = a;
		updateHeight(a); // 只需局部更新高度 插入操作如果局部更新成功，总体高度成功
		c->lc = T2;
		if(T2) T2->parent = c;
		c->rc = T3;
		if(T3) T3->parent = c;
		updateHeight(c);
		b->lc = a;
		b->rc = c;
		a->parent = b;
		c->parent = b;
		updateHeight(b);
		return b;
}


BinNode * insertNodeAVL(ElemType e , BinTree * binTree){
	BinNode * newNode = insertNode(binTree,e);
	BinNode * g , * parent ;
	for(g = newNode->parent;g;g = g->parent){
		//  一旦发现g失衡，则通过调整恢复平衡
		if(!AvlBanlance(g)){
			// g 失衡最少存在两级孩子
			// 在g中找到高度更高的孩子
			parent = g->parent;
			//FromParentTo(g,binTree) = rotateAt(tallerChild(tallerChild(g)));
			if(!IsRoot(g)){
				if(parent->lc == g)
					parent->lc = rotateAt(tallerChild(tallerChild(g)));
				else if(parent->rc == g)
					parent->rc = rotateAt(tallerChild(tallerChild(g)));
			} else {
				binTree->root = rotateAt(tallerChild(tallerChild(g)));
			}
			break;
		} else // 否则在原先平衡的祖先处，更新其高度，平衡性虽然不变，但是高度可能改变
			updateHeight(g);
	}
}

// 旋转
BinNode * rotateAt(BinNode * v){
	BinNode * p = v->parent;
	BinNode * g = p->parent;
	// 左左 或者左右
	if(IsLChild(v)){
		// 单旋转
		if(IsLChild(p)){
			p->parent = g->parent;
			return connect34 ( v, p, g, v->lc, v->rc, p->rc, g->rc );
		} 
		// 双旋转
		else {
			v->parent = g->parent;
			return connect34 ( p, v, g, p->lc, v->lc, v->rc, g->rc );
		}
	}
	// 右右 右左
	else {
		// 右右 单旋转
		if(IsRChild(v)){
			p->parent = g->parent;
			return connect34(g,p,v,g->lc,p->lc,v->lc,v->rc);
		} 
		// 右左 双旋转
		else {
			v->parent = g->parent;
			return connect34(g,v,p,g->lc,v->lc,v->rc,p->rc);
		}
	}
}

void deleteNodeAVL(BinTree * binTree , ElemType x){
	BinNode * g , * parent;
	BinNode * node = searchIn(root(binTree),x);
	if(node){
		g = node->parent;
		deleteNode(node);
		// 删除后可能导致失衡
		for(;g;g = g->parent){
			if(!AvlBanlance(g)){
				parent = g->parent;
				if(!IsRoot(g)){
					if(parent->lc == g){
					    parent->lc = rotateAt(tallerChild(tallerChild(g)));
						g = parent->lc;
					}
						
					else if(parent->rc == g){
						parent->rc = rotateAt(tallerChild(tallerChild(g)));
						g = parent->rc;
					}
					
				} else {
					binTree->root = rotateAt(tallerChild(tallerChild(g)));
					g = binTree->root;
				}
				updateHeight(g);
			}
		}
	}
}

*/