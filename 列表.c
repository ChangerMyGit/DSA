#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	ListNode * node;
	List * list = initList();
	for(i = 1;i <= 15;i++)
		insertBefore(i,list);
	node = list->header->succ;
	for(i = 1;i <= 15;i++)
		inserLast(i,list);
	printList(list);
	printf("%d\n",list->size);
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
	deduplicate(list);
	printList(list);
	return 0;
}