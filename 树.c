#include "BinTree.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	BinTree * tree = initBinTree();
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

	}
	return 0;
}