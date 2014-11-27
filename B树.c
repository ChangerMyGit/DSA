#include "Btree.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	int a[] = {202,100,60,300,50};
	BTNode * node = NULL;
	BTree * tree = initBtree(5);
	for(i = 0;i< 400;i++){
	    insertBtree(i,tree);
	}
	for(i = 100;i< 200 ;i++)
		removeBtree(i,tree);
	//printVector(tree->root->keys);
	//printf("\n");
	//removeBtree(161,tree);
/*
	node = searchBtree(163,tree);
	printVector(node->keys);
	printf("\n");
	printf("%d \n" , geiBTreeHigh(tree));
*/
	//removeBtree(80,tree);
	printBTree(tree);
	return 0;
}