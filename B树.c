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
	//printVector(tree->root->keys);
	//printf("\n");
	//removeBtree(80,tree);
	printVector(tree->root->keys);
	printf("\n");
	printf("%d \n" , geiBTreeHigh(tree));
	return 0;
}