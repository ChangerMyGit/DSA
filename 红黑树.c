#include "RedBlackTree.h"
#include <stdlib.h>
#include <stdio.h>

int mainRB(){
	int i;
	BinTree * tree = initBinTree();
	for(i = 1;i <= 20;i++)
		insertRBTree(i , tree);
	for(i = 1;i <= 3;i++)
		removeRBTree(i,tree);
	//removeRBTree(4,tree);
	if(tree->size!=0){
		printf("根节点：%d \n" , root(tree)->data);
		//printf("高度： %d\n",get_tree_height(root(tree)));
		printf("\n中序遍历---------------\n");
		travIn_R(root(tree));		
	}
	return 0;
}