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

void removeRBTree(ElemType x ,BinTree * tree){
	BinNode * r , * _hot;
	BinNode * xnode = searchIn(tree->root,x);
	if(!xnode) 
		return; // 不存在，返回
	r = deleteNode(xnode , tree);
	_hot = tree->_hot;
	if (!(--tree->size)) 
		return ; //实施删除
	if (!_hot){  //若刚被删除的是根节点，则将其置黑，并更新黑高度
		tree->root->color = BLACK;
		updateHeight (tree->root);
		return;
	} 
	if (IsRed(r)) { //否则，若r为红，则只需令其转黑
		r->color = BLACK; 
		r->height++;
		return;
	}
	solveDoubleBlack(r,tree);
}

/*************************************************************************
* RedBlack双黑调整算法：解决节点x与被其替代的节点均为黑色的问题
* 分为三大类共四种情况：
*    BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
*    BB-2R：2次颜色翻转，2次黑高度更新，0次旋转，不再递归
*    BB-2B：1次颜色翻转，1次黑高度更新，0次旋转，需要递归
*    BB-3 ：2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB2R
**************************************************************************/
void solveDoubleBlack(BinNode * r ,BinTree * tree){
	BinNode * p = r ? r->parent : tree->_hot;
	BinNode * s = (r == p->lc) ? p->rc : p->lc; //r的兄弟
	BinNode * t = NULL , * b ,* gg;
	Color oldColor ;// 旧的颜色
	if(!p) 
		return;
	gg = p->parent;
	if(!s) return;
	if(IsBlack(s)) { //兄弟s为黑
		//s的红孩子（若左、右孩子皆红，左者优先；皆黑时为NULL）
		if(HasLChild(s) && IsRed(s->lc)) 
			t = s->lc;
		else if (HasRChild (s) && IsRed(s->rc)) 
			t = s->rc;
		if(t){ //黑s有红孩子：BB-1
			oldColor = p->color;//备份原子树根节点p颜色，并对t及其父亲、祖父
			//重平衡，并将新子树的左、右孩子染黑
			b = rotateAt(t);
			if(!IsRoot(p)){
				if(gg->lc == p){
					gg->lc = b;
					p = gg->lc;
				}
				else if(gg->rc == p){
					gg->rc = b;
					p = gg->rc;
				}
			} else {
				tree->root = b;
			} 
			if (b->lc)   //左孩子
				b->lc->color = BLACK; 
			updateHeight (b->lc);
			if (b->rc)  //右孩子
				b->rc->color = BLACK; 
			updateHeight ( b->rc );
			b->color = oldColor; 
			updateHeight (b); //新子树根节点继承原根节点的颜色
		} else { //黑s无红孩子
			s->color = RED; 
			s->height--; //s转红
			if (IsRed(p)) { //BB-2R
				p->color = BLACK; //p转黑，但黑高度不变
			} else { //BB-2B
				p->height--; //p保持黑，但黑高度下降
				solveDoubleBlack (p,tree);
			}
		}
	} else { //兄弟s为红：BB-3
		s->color = BLACK; 
		p->color = RED; //s转黑，p转红
		t = IsLChild(s) ? s->lc : s->rc; //取t与其父s同侧
		tree->_hot = p;
		b = rotateAt(t);//对t及其父亲、祖父做平衡调整
		if(!IsRoot(p->parent)){
			if(IsLChild(p))
				p->parent->lc = b;
			else if(IsRChild(p))
				p->parent->rc = b;
		} else {
			tree->root = b;
		}
		solveDoubleBlack (r,tree); //继续修正r处双黑——此时的p已转红，故后续只能是BB-1或BB-2R
	}
}