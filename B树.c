#include "Btree.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	int a[] = {202,100,60,300,50};
	BTNode * node = NULL;
	BTree * tree = initBtree(5);
	for(i = 0;i< 40;i++){
	    insertBtree(i,tree);
	}
	//printVector(tree->root->keys);
	node = searchBtree(3,tree);
	return 0;
}