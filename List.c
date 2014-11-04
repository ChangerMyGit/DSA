#include "List.h"
#include <stdio.h>
#include <stdlib.h>

/**
   问题记录:创建新节点的时候，应该使用malloc 向堆内存中申请，类似于new
**/
List * initList(){
	List * list;
	// 需要向堆申请内存，否则函数运行结束后 引用消失
	ListNode * header , * trailer;
	header = (ListNode *)malloc(sizeof(ListNode));
	trailer = (ListNode *)malloc(sizeof(ListNode));
	list = (List *)malloc(sizeof(List));
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

ListNode * getFirst(List * list){
	if(list->size > 0)
		return list->header->succ;
	return NULL;
}

ListNode * getLast(List * list){
	if(list->size > 0)
		return list->trailer->pre;
	return NULL;
}

ListNode * findList(int data,List * list){
	int i;
	ListNode * node = getFirst(list);
	for(i = 0;i < list->size ; i++){
		if(node->data == data)
			return node;
		node = node->succ;
	}
	return NULL;
}