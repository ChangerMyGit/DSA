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
	    printf("�߶ȣ� %d\n",getTreeHeight(tree));
		printf("�߶ȣ� %d\n",get_tree_height(root(tree)));
		printf("�ڵ���Ŀ��%d\n",getBinNodeSize(root(tree)));
		printf("ǰ�����---------------\n");
		travPre(root(tree));
		printf("\n");
		travPre_I1(root(tree));
		printf("\n");
		travPre_I2(root(tree));
		printf("\n�������---------------\n");
		travIn_R(root(tree));
		printf("\n");
		travIn_I1(root(tree));
		printf("\n��α���---------------\n");
		traveLevel(root(tree));
		printf("\nҶ�ӽڵ���Ŀ %d \n ",getLeafNum(root(tree)));

	}
	return 0;
}