#include "BinTree.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
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
		/*
		insertNode(tree,16);
		insertNode(tree,10);
		insertNode(tree,25);
		insertNode(tree,19);
		insertNode(tree,28);
		insertNode(tree,5);
		insertNode(tree,11);
		insertNode(tree,3);
		insertNode(tree,33);
		*/
		for(i = 1 ; i < 20 ; i++){
		   insertNode(tree,i);
		}
	}
	if(tree->size!=0){
	    printf("高度： %d\n",getTreeHeight(tree));
        printf("\n中序遍历---------------\n");
		travIn_R(root(tree));
		//searchIn(root(tree),11,hot);
		printf("\n %d ",searchIn(root(tree),11)->data);
		printf("\n");
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