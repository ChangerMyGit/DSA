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
		// ɾ������ܵ���ʧ��
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

// ��ת
BinNode * rotateAt(BinNode * v){
	BinNode * p = v->parent;
	BinNode * g = p->parent;
	// ���� ��������
	if(IsLChild(v)){
		// ����ת
		if(IsLChild(p)){
			p->parent = g->parent;
			return connect34 ( v, p, g, v->lc, v->rc, p->rc, g->rc );
		} 
		// ˫��ת
		else {
			v->parent = g->parent;
			return connect34 ( p, v, g, p->lc, v->lc, v->rc, g->rc );
		}
	}
	// ���� ����
	else {
		// ���� ����ת
		if(IsRChild(v)){
			p->parent = g->parent;
			return connect34(g,p,v,g->lc,p->lc,v->lc,v->rc);
		} 
		// ���� ˫��ת
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
		updateHeight(a); // ֻ��ֲ����¸߶� �����������ֲ����³ɹ�������߶ȳɹ�
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
		//  һ������gʧ�⣬��ͨ�������ָ�ƽ��
		if(!AvlBanlance(g)){
			// g ʧ�����ٴ�����������
			// ��g���ҵ��߶ȸ��ߵĺ���
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
		} else // ������ԭ��ƽ������ȴ���������߶ȣ�ƽ������Ȼ���䣬���Ǹ߶ȿ��ܸı�
			updateHeight(g);
	}
}