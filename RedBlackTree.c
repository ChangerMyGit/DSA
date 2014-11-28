#include "RedBlackTree.h"
#include <stdlib.h>
#include <stdio.h>

void insertRBTree(ElemType x ,BinTree * tree){
	BinNode * node = insertNode(tree,x);	
	solveDoubleRed(node,tree);
}

/****************************************************************************
* RedBlack双红调整算法：解决节点x与其父均为红色的问题。分为两大类情况：
*    RR-1：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
*    RR-2：3次颜色翻转，3次黑高度更新，0次旋转，需要递归
******************************************************************************************/
void solveDoubleRed(BinNode * x ,BinTree * tree){
	BinNode * p , * u , * g , * gg;
	//若已（递归）转至树根，则将其转黑，整树黑高度也随之递增
	if(IsRoot(x)){
		tree->root->color = BLACK;
		tree->root->height++;
		return;
	}
	p = x->parent;
	if(IsBlack(p)) //若p为黑，则可终止调整。否则
		return;
	g = p->parent; // 既然p为红，则x的祖父必存在，且必为黑色
	u = getUncle(x);//以下，视x叔父u的颜色分别处理
	if (IsBlack(u)) { //u为黑色（含NULL）时
		if (IsLChild(x) == IsLChild(p)) //若x与p同侧（即zIg-zIg或zAg-zAg），则
			p->color = BLACK; //p由红转黑，x保持红
		else//若x与p异侧（即zIg-zAg或zAg-zIg），则
			x->color = BLACK; //x由红转黑，p保持红
		g->color = RED; //g必定由黑转红
		//以上虽保证总共两次染色，但因增加了判断而得不偿失
		// 在旋转后将根置黑、孩子置红，虽需三次染色但效率更高
		gg = g->parent;
		if(!IsRoot(g)){
			if(gg->lc == g){
				gg->lc = rotateAt(x);
				g = gg->lc;			
			} else if(gg->rc == g){
				gg->rc = rotateAt(x);
				g = gg->rc;
			}
		} else {
			tree->root = rotateAt(x);
		}
	} else { //若u为红色
		p->color = BLACK; p->height++; //p由红转黑
		u->color = BLACK; u->height++; //u由红转黑
		if (!IsRoot (g)) g->color = RED; //g若非根，则转红
		solveDoubleRed(g,tree); //继续调整g（类似于尾递归，可优化为迭代形式）
	}
}

BinNode * getUncle(BinNode * binNode){
	BinNode * g;
	if(IsRoot(binNode) || IsRoot(binNode->parent))
		return NULL;
	g = binNode->parent->parent;
	if(IsLChild(binNode->parent))
		return g->rc;
	else 
		return g->lc;
}