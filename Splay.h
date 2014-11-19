#ifndef _SPLAY_H
#define _SPLAY_H

#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "BinTree.h"

// ��չ
BinNode * splay(BinNode * v);
// ��չ���Ĳ���
BinNode * searchSplay(BinTree * tree , ElemType e);
// ��չ���Ĳ���
BinNode * insertSplay(BinTree * tree , ElemType e);
// ��չ����ɾ��
void deleteSplay(BinTree * tree , ElemType e);
#endif