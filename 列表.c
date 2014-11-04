#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int a[] = {1,1,2,2,3,3,4,4,5,5,6,6};
	int i;
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
	node = findList(6,list);
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
	//deduplicate(list);
	uniquifyBySort(list);
	printList(list);
	//clearList(list);
	//printList(list);
	//printf("%d %d \n",&a[0],&a[1]);
	return 0;
}