#include "BinTree.h"
#include "Splay.h"
#include <stdio.h>
#include <stdlib.h>

BinNode * searchSplay(BinTree * tree , ElemType e){
	BinNode * parent;
	BinNode * rootNode = root(tree);
	parent = rootNode->parent;
	while(rootNode){
		if(rootNode->data == e){
			splay(rootNode);
			tree->root = rootNode;
			return rootNode;
		}
		else if(rootNode->data > e){
			parent = rootNode;
			rootNode = rootNode->lc;		
		}
		else if(rootNode->data < e){
			parent = rootNode;
			rootNode = rootNode->rc;
		}	
	}
	splay(parent);
	tree->root = parent;
	return parent;
}

BinNode * insertSplay(BinTree * tree , ElemType e){
	BinNode * newNode , * binNode;
	binNode = searchSplay(tree,e);
	if(binNode->data != e){
		newNode = newBinNode(e,NULL);
		if(e > root(tree)->data){
			newNode->lc = root(tree);
			tree->root->parent = newNode;
		}
		else {
			newNode->rc = root(tree);
			tree->root->parent = newNode;
		}
		tree->root = newNode;	
	}
}


void deleteSplay(BinTree * tree , ElemType e){
	BinNode * binNode;
	binNode = searchSplay(tree,e);
	if(binNode->data == e)
		deleteNode(binNode,tree);
}

void attachAsLChild(BinNode * p , BinNode * lc){
	p->lc = lc; 
	if (lc) 
		lc->parent = p;
}

void attachAsRChild(BinNode * p , BinNode * rc){
	p->rc = rc; 
	if (rc)
		rc->parent = p;
}
//Splay����չ�㷨���ӽڵ�v���������չ
BinNode * splay(BinNode * v){//vΪ��������ʶ�����չ�Ľڵ�λ��
	BinNode * p , * g; //v�ĸ������游
	if(!v) return NULL;
	//���¶��ϣ�������v��˫����չ
	while ( ( p = v->parent ) && ( g = p->parent ) ) {
		//ÿ��֮��*v����ԭ���游��great-grand parent��Ϊ��
		// �˴�����ת ��AVL ��ͬ ����Ҫ�ж�ƽ������
		// zig-zag �� zag-zig ��AVL��תһ�� ���ڸ��ڵ���ת�ٺ��游�ڵ���ת
		// zig-zig �� zag-zag ��AVL��ͬ�����Ǹ��ڵ���游�ڵ���ת��Ȼ���ٺ��ӽڵ���ת
		// ÿ����չ֮�� ��ʹ���ĸ߶Ƚ��� ������ �ή��һ��
		BinNode * gg = g->parent; 
		if ( IsLChild ( v ) )
			if ( IsLChild ( p ) ) { 
				//zig-zig
				attachAsLChild ( g, p->rc ); 
				attachAsLChild ( p, v->rc );
				attachAsRChild ( p, g ); 
				attachAsRChild ( v, p );
			}else { 
				//zig-zag
				attachAsLChild ( p, v->rc ); 
				attachAsRChild ( g, v->lc );
				attachAsLChild ( v, g ); 
				attachAsRChild ( v, p );
			}
		else if ( IsRChild ( p ) ) { 
			//zag-zag
			attachAsRChild ( g, p->lc ); 
			attachAsRChild ( p, v->lc );
			attachAsLChild ( p, g ); 
			attachAsLChild ( v, p );
		}
		else { 
			//zag-zig
			attachAsRChild ( p, v->lc ); 
			attachAsLChild ( g, v->rc );
			attachAsRChild ( v, g ); 
			attachAsLChild ( v, p );
		}
		//��*vԭ�ȵ����游*gg�����ڣ���*v����ӦΪ����
		if ( !gg ) v->parent = NULL; 
		else //����*gg�˺�Ӧ����*v��Ϊ����Һ���
			( g == gg->lc ) ? attachAsLChild ( gg, v ) : attachAsRChild ( gg, v );
		updateHeight ( g ); 
		updateHeight ( p ); 
		updateHeight ( v );
	}
	//˫����չ����ʱ������g == NULL����p���ܷǿ�
	if ( p = v->parent ) { //��p����ǿգ����������һ�ε���
		if ( IsLChild ( v ) ) { 
			attachAsLChild ( p, v->rc ); 
			attachAsRChild ( v, p ); 
		} else {
			attachAsRChild ( p, v->lc ); 
			attachAsLChild ( v, p ); 
		}
		updateHeight ( p ); 
		updateHeight ( v );
	}
	v->parent = NULL; 
	return v;
}