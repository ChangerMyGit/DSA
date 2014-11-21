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
//Splay树伸展算法：从节点v出发逐层伸展
BinNode * splay(BinNode * v){//v为因最近访问而需伸展的节点位置
	BinNode * p , * g; //v的父亲与祖父
	if(!v) return NULL;
	//自下而上，反复对v做双层伸展
	while ( ( p = v->parent ) && ( g = p->parent ) ) {
		//每轮之后*v都以原曾祖父（great-grand parent）为父
		// 此处的旋转 与AVL 不同 不需要判断平衡的情况
		// zig-zag 和 zag-zig 与AVL旋转一样 先于父节点旋转再和祖父节点旋转
		// zig-zig 和 zag-zag 与AVL不同，先是父节点和祖父节点旋转，然后再和子节点旋转
		// 每次伸展之后 会使数的高度降低 最好情况 会降低一半
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
		//若*v原先的曾祖父*gg不存在，则*v现在应为树根
		if ( !gg ) v->parent = NULL; 
		else //否则，*gg此后应该以*v作为左或右孩子
			( g == gg->lc ) ? attachAsLChild ( gg, v ) : attachAsRChild ( gg, v );
		updateHeight ( g ); 
		updateHeight ( p ); 
		updateHeight ( v );
	}
	//双层伸展结束时，必有g == NULL，但p可能非空
	if ( p = v->parent ) { //若p果真非空，则额外再做一次单旋
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