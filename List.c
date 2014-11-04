#include "List.h"
#include <stdio.h>
#include <stdlib.h>

/**
   �����¼:�����½ڵ��ʱ��Ӧ��ʹ��malloc ����ڴ������룬������new
**/
List * initList(){
	List * list;
	// ��Ҫ��������ڴ棬���������н����� ������ʧ
	ListNode * header , * trailer;
	header = (ListNode *)malloc(sizeof(ListNode));
	trailer = (ListNode *)malloc(sizeof(ListNode));
	list = (List *)malloc(sizeof(List));
	/**
	  �ڱ��ڵ㻥��
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
		// �½ڵ��ǰ�����б��ǰ�ڱ��ڵ㣬�����ǰ�ڱ��ڵ�ĺ��
		newListNode(newNode , data , list->header,list->header->succ);
		list->header->succ->pre = newNode;
		list->header->succ = newNode;
		list->size++;
	}
}

void inserLast(int data , List * list){
	ListNode * newNode = (ListNode *)malloc(sizeof(ListNode));
	if(newNode != NULL){
		// �½ڵ�ĺ���Ǻ��ڱ��ڵ㣬ǰ���Ǻ��ڱ��ڵ��ǰ��
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