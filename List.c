#include "List.h"
#include <stdio.h>
#include <stdlib.h>

void initList(List * list){
	// 需要向堆申请内存，否则函数运行结束后 引用消失
	ListNode * header , * trailer;
	header = (ListNode *)malloc(sizeof(ListNode));
	trailer = (ListNode *)malloc(sizeof(ListNode));
	/**
	  哨兵节点互联
	**/
	header->succ = trailer;
	header->pre = NULL;
	trailer->pre = header;
	trailer->succ = NULL;
	list->header = header;
	list->trailer = trailer;
	list->size = 0;
}

void newListNode(ListNode * newNode , int data , ListNode * pre , ListNode * succ){
	newNode->data = data;
	newNode->pre = pre;
	newNode->succ = succ;
}

void insertBefore(int data , List * list){
	ListNode * newNode = (ListNode *)malloc(sizeof(ListNode));
	if(newNode != NULL){
		// 新节点的前驱是列表的前哨兵节点，后继是前哨兵节点的后继
		newListNode(newNode , data , list->header,list->header->succ);
		list->header->succ->pre = newNode;
		list->header->succ = newNode;
		list->size++;
	}
}

void inserLast(int data , List * list){
	ListNode * newNode = (ListNode *)malloc(sizeof(ListNode));
	if(newNode != NULL){
		// 新节点的后继是后哨兵节点，前驱是后哨兵节点的前驱
		newListNode(newNode , data , list->trailer->pre,list->trailer);
		list->trailer->pre->succ = newNode;
		list->trailer->pre = newNode;
		list->size++;
	}
}