#include "BinTree.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	BinTree * tree = initBinTree();
	if(tree->size == 0){
		insertAsRoot(tree,10);
		insertAsLC(6,root(tree));
		insertAsRC(16,root(tree));
		printf("%d\n",root(tree)->data);
	}
	return 0;
}