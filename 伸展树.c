#include "BinTree.h"
#include "Queue.h"
#include "Splay.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	BinNode * binNode;
	BinTree * tree = initBinTree();
	for(i = 1 ; i <= 8 ; i++){
		insertNode(tree,i);
	} 
	//searchSplay(tree,7);
	//searchSplay(tree,8);
	//insertSplay(tree,7);
	insertSplay(tree,7);
	insertSplay(tree,8);
	deleteSplay(tree,6);
	if(tree->size!=0){
		printf("根节点：%d \n" , root(tree)->data);
	    printf("高度： %d\n",get_tree_height(root(tree)));
        printf("\n中序遍历---------------\n");
		travIn_R(root(tree));
		printf("\n");	
	}
	return 0;
}