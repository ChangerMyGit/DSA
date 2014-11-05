#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int mainList(){
	int a[] = {1,1,6,6,3,3,11,11,5,5,10,10,4,4,2,2,9,9};
	int i;
	// 通用类型
	//ElemType x = 'x';
	ListNode * node;
	List * list = initList();
/**
    for(i = 1;i <= 15;i++)
		insertBefore(i,list);
	node = list->header->succ;
	for(i = 1;i <= 15;i++)
		//insertBefore(i,list);
		inserLast(i,list);
**/	
	for(i = 0;i < ((sizeof(a)/sizeof(int)));i++)
		inserLast(a[i],list);
	printList(list);
	//printf("%d\n",list->size);
	node = getFirst(list);
	//clearList(list);
/*
   if(node != NULL){
		printf("%d\n",node->data);
		node = findAfterListNode(10,node,16);
		node = findBeforeListNode(10,20,node);
		if(node != NULL)
		   printf("%d\n",node->data);
		//deleteListNode(node);
	}
*/ 
	// 无序去重
	// deduplicate(list);
	// 选择排序
	// selectionSort(list);
	// 有序去重
    uniquifyBySort(list);
	// 插入排序
	insertionSort(list);
	// insertBeforeNode(16,node);
	// insertAfterNode(19,getLast(list));
	printList(list);
	//printf("\n%d \n",selectMax(list,list->size)->data);
	//clearList(list);
	//printList(list);
	//printf("%d %d \n",&a[0],&a[1]);
	//printf("%c\n",x);
	return 0;
}