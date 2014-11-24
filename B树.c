#include "Btree.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	int a[] = {100,202,300};
	BTNode * node = NULL;
	/*
	int i;
	int a[] = {6,202,100,301,38,8,1,201,300,16};
	Vector * vec = initVector(10 * sizeof(int));
	for(i = 0;i < sizeof(a) / sizeof(int); i++)
	insert(vec,a[i]);
	sort(vec);
	printVector(vec);
	printf("\n");
	printf("%d\n",binSearchInChild(vec,0,vec->size,101));
	*/
	BTree * tree = initBtree(4);
	tree->root = newBTNode(NULL,tree->_order,3 * sizeof(int));
	for(i = 0;i< sizeof(a)/sizeof(int);i++)
		insert(tree->root->keys,a[i]);
	for(i = 0;i < tree->_order;i++)
		insert(tree->root->child,NULL); 
	node = searchBtree(300, tree);
	if(node){
		printf("%d\n",node->keys->elem[0]);
	}
	return 0;
}