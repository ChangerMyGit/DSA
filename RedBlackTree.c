#include "RedBlackTree.h"
#include <stdlib.h>
#include <stdio.h>

void insertRBTree(ElemType x ,BinTree * tree){
	BinNode * node = insertNode(tree,x);	
	solveDoubleRed(node,tree);
}

/****************************************************************************
* RedBlack˫������㷨������ڵ�x���丸��Ϊ��ɫ�����⡣��Ϊ�����������
*    RR-1��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
*    RR-2��3����ɫ��ת��3�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
******************************************************************************************/
void solveDoubleRed(BinNode * x ,BinTree * tree){
	BinNode * p , * u , * g , * gg;
	//���ѣ��ݹ飩ת������������ת�ڣ������ڸ߶�Ҳ��֮����
	if(IsRoot(x)){
		tree->root->color = BLACK;
		tree->root->height++;
		return;
	}
	p = x->parent;
	if(IsBlack(p)) //��pΪ�ڣ������ֹ����������
		return;
	g = p->parent; // ��ȻpΪ�죬��x���游�ش��ڣ��ұ�Ϊ��ɫ
	u = getUncle(x);//���£���x�常u����ɫ�ֱ���
	if (IsBlack(u)) { //uΪ��ɫ����NULL��ʱ
		if (IsLChild(x) == IsLChild(p)) //��x��pͬ�ࣨ��zIg-zIg��zAg-zAg������
			p->color = BLACK; //p�ɺ�ת�ڣ�x���ֺ�
		else//��x��p��ࣨ��zIg-zAg��zAg-zIg������
			x->color = BLACK; //x�ɺ�ת�ڣ�p���ֺ�
		g->color = RED; //g�ض��ɺ�ת��
		//�����䱣֤�ܹ�����Ⱦɫ�������������ж϶��ò���ʧ
		// ����ת�󽫸��úڡ������ú죬��������Ⱦɫ��Ч�ʸ���
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
	} else { //��uΪ��ɫ
		p->color = BLACK; p->height++; //p�ɺ�ת��
		u->color = BLACK; u->height++; //u�ɺ�ת��
		if (!IsRoot (g)) g->color = RED; //g���Ǹ�����ת��
		solveDoubleRed(g,tree); //��������g��������β�ݹ飬���Ż�Ϊ������ʽ��
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
		return; // �����ڣ�����
	r = deleteNode(xnode , tree);
	_hot = tree->_hot;
	if (!(--tree->size)) 
		return ; //ʵʩɾ��
	if (!_hot){  //���ձ�ɾ�����Ǹ��ڵ㣬�����úڣ������ºڸ߶�
		tree->root->color = BLACK;
		updateHeight (tree->root);
		return;
	} 
	if (IsRed(r)) { //������rΪ�죬��ֻ������ת��
		r->color = BLACK; 
		r->height++;
		return;
	}
	solveDoubleBlack(r,tree);
}

/*************************************************************************
* RedBlack˫�ڵ����㷨������ڵ�x�뱻������Ľڵ��Ϊ��ɫ������
* ��Ϊ�����๲���������
*    BB-1 ��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
*    BB-2R��2����ɫ��ת��2�κڸ߶ȸ��£�0����ת�����ٵݹ�
*    BB-2B��1����ɫ��ת��1�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
*    BB-3 ��2����ɫ��ת��2�κڸ߶ȸ��£�1����ת��תΪBB-1��BB2R
**************************************************************************/
void solveDoubleBlack(BinNode * r ,BinTree * tree){
	BinNode * p = r ? r->parent : tree->_hot;
	BinNode * s = (r == p->lc) ? p->rc : p->lc; //r���ֵ�
	BinNode * t = NULL , * b ,* gg;
	Color oldColor ;// �ɵ���ɫ
	if(!p) 
		return;
	gg = p->parent;
	if(!s) return;
	if(IsBlack(s)) { //�ֵ�sΪ��
		//s�ĺ캢�ӣ������Һ��ӽԺ죬�������ȣ��Ժ�ʱΪNULL��
		if(HasLChild(s) && IsRed(s->lc)) 
			t = s->lc;
		else if (HasRChild (s) && IsRed(s->rc)) 
			t = s->rc;
		if(t){ //��s�к캢�ӣ�BB-1
			oldColor = p->color;//����ԭ�������ڵ�p��ɫ������t���丸�ס��游
			//��ƽ�⣬���������������Һ���Ⱦ��
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
			if (b->lc)   //����
				b->lc->color = BLACK; 
			updateHeight (b->lc);
			if (b->rc)  //�Һ���
				b->rc->color = BLACK; 
			updateHeight ( b->rc );
			b->color = oldColor; 
			updateHeight (b); //���������ڵ�̳�ԭ���ڵ����ɫ
		} else { //��s�޺캢��
			s->color = RED; 
			s->height--; //sת��
			if (IsRed(p)) { //BB-2R
				p->color = BLACK; //pת�ڣ����ڸ߶Ȳ���
			} else { //BB-2B
				p->height--; //p���ֺڣ����ڸ߶��½�
				solveDoubleBlack (p,tree);
			}
		}
	} else { //�ֵ�sΪ�죺BB-3
		s->color = BLACK; 
		p->color = RED; //sת�ڣ�pת��
		t = IsLChild(s) ? s->lc : s->rc; //ȡt���丸sͬ��
		tree->_hot = p;
		b = rotateAt(t);//��t���丸�ס��游��ƽ�����
		if(!IsRoot(p->parent)){
			if(IsLChild(p))
				p->parent->lc = b;
			else if(IsRChild(p))
				p->parent->rc = b;
		} else {
			tree->root = b;
		}
		solveDoubleBlack (r,tree); //��������r��˫�ڡ�����ʱ��p��ת�죬�ʺ���ֻ����BB-1��BB-2R
	}
}