#include "BinTree.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>
#include "AVLTree.h"

int mainAVL(){
	int i;
	BinTree * tree = initBinTree();
	for(i = 1;i<=10;i++)
		insertNodeAVL(i , tree);
	if(tree->size!=0){
		printf("���ڵ㣺%d \n" , root(tree)->data);
		printf("�߶ȣ� %d\n",get_tree_height(root(tree)));
		printf("\n�������---------------\n");
		travIn_R(root(tree));	    
	}
	for(i = 1 ;i < 7 ; i++)
		deleteNodeAVL(tree , (ElemType)i);
	if(tree->size!=0){
		printf("���ڵ㣺%d \n" , root(tree)->data);
		printf("�߶ȣ� %d\n",get_tree_height(root(tree)));
		printf("\n�������---------------\n");
		travIn_R(root(tree));
	}
	return 0;
}