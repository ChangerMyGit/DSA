#include "BinTree.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	BinTree * tree = initBinTree();
	if(tree->size == 0){
		insertAsRoot(tree,10);
		insertAsLC(6,root(tree));
		insertAsRC(16,root(tree));
		insertAsRC(26,root(tree)->rc);
		insertAsRC(36,root(tree)->rc->rc);
		insertAsLC(3,root(tree)->lc);
		insertAsLC(2,root(tree)->lc->lc);
		insertAsLC(1,root(tree)->lc->lc->lc);

	}
	if(tree->size!=0){
	    printf("�߶ȣ� %d\n",getTreeHeight(tree));
		printf("�ڵ���Ŀ��%d\n",getBinNodeSize(root(tree)));
		travPre(root(tree));
		//travPre_I1(root(tree));
	}
	return 0;
}