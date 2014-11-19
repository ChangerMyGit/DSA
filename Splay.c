#include "BinTree.h"
#include "Splay.h"
#include <stdio.h>
#include <stdlib.h>

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