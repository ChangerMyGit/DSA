#include "BinTree.h"
#include "Queue.h"
#include "Splay.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	BinNode * binNode;
	BinTree * tree = initBinTree();
	for(i = 1 ; i <= 10 ; i++){
		insertNode(tree,i);
	} 
	binNode = getMax(root(tree));
	splay(binNode);
	tree->root = binNode;
	if(tree->size!=0){
		printf("���ڵ㣺%d \n" , root(tree)->data);
	    printf("�߶ȣ� %d\n",get_tree_height(root(tree)));
        printf("\n�������---------------\n");
		travIn_R(root(tree));
		printf("\n");	
	}
	return 0;
}