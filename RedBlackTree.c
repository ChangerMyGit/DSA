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