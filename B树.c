#include "Btree.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	int a[] = {202,100,60,300,50};
	BTNode * node = NULL;
	BTree * tree = initBtree(5);
	for(i = 0;i< sizeof(a)/sizeof(int);i++)
		insertBtree(a[i],tree);
	//printVector(tree->root->keys);
	node = searchBtree(100,tree);
	if(node){
		printf("%d \n" , node->keys->elem[0]);
	}
	return 0;
}