#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	ListNode * node;
	List * list = (List *)malloc(sizeof(List));
	initList(list);
	for(i = 1;i <= 15;i++)
		insertBefore(i,list);
	node = list->header->succ;
	for(i = 1;i <= 15;i++)
		inserLast(i,list);
	for(i = list->size;i>0;i--){
		printf("%d ",node->data);
		node = node->succ;
	}
	printf("\n");
	printf("%d\n",list->size);
	return 0;
}