#include "BinTree.h"
#include "Stack.h"
#include "AVLTree.h"
#include <stdlib.h>
#include <stdio.h>

void deleteNodeAVL(BinTree * binTree , ElemType x){
	BinNode * g , * parent;
	BinNode * node = searchIn(root(binTree),x);
	if(node){
		g = node->parent;
		deleteNode(node,binTree);
		binTree->size--;
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