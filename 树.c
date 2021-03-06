#include "BinTree.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>
#include "AVLTree.h"

int mainTree(){
    int i;
	BinTree * tree = initBinTree();
	if(tree->size == 0){
		/*
	    insertAsRoot(tree,16);
		insertAsLC(10,root(tree));
		insertAsRC(25,root(tree));
		insertAsLC(19,root(tree)->rc);
		insertAsRC(28,root(tree)->rc);
		insertAsLC(5,root(tree)->lc);
		insertAsRC(11,root(tree)->lc);
		//insertNode(tree,3);
		*/
		/*insertNode(tree,16);
		insertNode(tree,10);
		insertNode(tree,25);
		insertNode(tree,19);
		insertNode(tree,28);
		insertNode(tree,5);
		insertNode(tree,11);
		insertNode(tree,4);
		insertNode(tree,33);
		insertNodeAVL(36,tree);
		insertNodeAVL(38,tree);
		insertNodeAVL(39,tree);
		insertNodeAVL(40,tree);
		insertNodeAVL(41,tree);
		*/
		/* 
		insertNodeAVL(3,tree);
		insertNodeAVL(5,tree);
		insertNodeAVL(11,tree);
		insertNodeAVL(16,tree);
		insertNodeAVL(19,tree);
		insertNodeAVL(25,tree);
		insertNodeAVL(28,tree);
		insertNodeAVL(33,tree);
		insertNodeAVL(36,tree);
		insertNodeAVL(39,tree);
		insertNodeAVL(41,tree);
		insertNodeAVL(43,tree);
		deleteBinNode(tree,28);
		deleteBinNode(tree,5);
		deleteBinNode(tree,25);
		deleteBinNode(tree,3);
		deleteBinNode(tree,33); */
		for(i = 1 ; i < 10 ; i++){
		   insertNodeAVL(i,tree);
		} 
	}
	if(tree->size!=0){
		printf("根节点：%d \n" , root(tree)->data);
	    printf("高度： %d\n",get_tree_height(root(tree)));
        printf("\n中序遍历---------------\n");
		travIn_R(root(tree));
		//printf("\n %d ",searchIn(root(tree),11)->data);
		//printf("\n %d ", getMax(root(tree))->data);
		//printf("\n %d ", getMin(root(tree))->data);
		printf("\n");
	}
    for(i = 1 ;i < 8 ; i++)
		deleteBinNode(tree,i);
		//deleteNodeAVL(tree , i);
	if(tree->size!=0){
		printf("根节点：%d \n" , root(tree)->data);
		printf("高度： %d\n",get_tree_height(root(tree)));
        printf("\n中序遍历---------------\n");
		travIn_R(root(tree));
	}
	/*
	if(tree->size == 0){
		insertAsRoot(tree,'A');
		insertAsLC('B',root(tree));
		insertAsRC('E',root(tree));
		insertAsRC('G',root(tree)->rc);
		insertAsLC('F',root(tree)->rc);
		insertAsLC('C',root(tree)->lc);
		insertAsRC('D',root(tree)->lc);
	}
	if(tree->size!=0){
	    printf("高度： %d\n",getTreeHeight(tree));
		printf("高度： %d\n",get_tree_height(root(tree)));
		printf("节点数目：%d\n",getBinNodeSize(root(tree)));
		printf("前序遍历---------------\n");
		travPre(root(tree));
		printf("\n");
		travPre_I1(root(tree));
		printf("\n");
		travPre_I2(root(tree));
		printf("\n中序遍历---------------\n");
		travIn_R(root(tree));
		printf("\n");
		travIn_I1(root(tree));
		printf("\n层次遍历---------------\n");
		traveLevel(root(tree));
		printf("\n叶子节点数目 %d \n ",getLeafNum(root(tree)));
		//printf("\n%c",search(root(tree),'C')->data);
	}  */
	return 0;
}