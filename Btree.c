#include "Btree.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

BTree * initBtree(int order){
	BTree * tree = (BTree *)malloc(sizeof(BTree));
	tree->root = NULL;
	tree->hot = NULL;
	tree->size = 0;
	tree->_order = order;
}

BTNode * newBTNode(BTNode * parent , int order ,int keys_Length){
	BTNode * node = (BTNode *)malloc(sizeof(BTNode));
	node->parent = parent;
	// 至多M个孩子
	node->child = initVector(order * sizeof(BTNode *));
	// 至多M-1个关键码
	node->keys = initVector(keys_Length);
	setAllValue(node->child,NULL,order);
	setAllValue(node->keys,NULL,order-1);
	return node;
}

BTNode * searchBtree(Elem e , BTree * tree){
	int r;
	BTNode * v  = tree->root;
	BTNode * hot = NULL;
	while(v){
		r = searchInChild(e,v->keys);
		if(v->keys->elem[r] == e) 
			return v; // 返回节点
		hot = v; 
		tree->hot = hot;
		v = (BTNode *)v->child->elem[r+1];
	}
	return NULL;
}

int searchInChild(Elem e , Vector * keys){
	int lo = 0;
	int hi = keys->size;
	int r = binSearchInChild(keys,lo,hi,e);
	return r;
}

int binSearchInChild(Vector * keys,int lo , int hi,int key){
	int mi;
	if(hi == 0) return -1;
	else if(lo == hi) return lo -1;
	else if(lo < hi){
		mi = (lo + hi) >> 1;
		if(keys->elem[mi] == key) return mi;
		else if(keys->elem[mi] > key) return binSearchInChild(keys,lo,mi,key);
		else if(keys->elem[mi] < key) return binSearchInChild(keys,mi+1,hi,key);
	}
	return lo;
}

void solveOverflow(BTNode * btNode,BTree * tree){
	BTNode * u , * temp , * p;
	int s , i;
	Elem e , shangyi;
	if(tree->_order > btNode->keys->size) 
		return; //递归基：当前节点并未上溢
	// 轴点（此时应有_order = key.size() = child.size() - 1）
	s = tree->_order/2;
	// 上溢节点
	shangyi = getElem(btNode->keys,s);
	// 创建新的节点
	u = newBTNode(NULL,s, (s - 1) * sizeof(int));
	// 分裂孩子关系 从S+1 开始 到 order 结束
	for(i = s + 1;i <= tree->_order;i++){
		temp = (BTNode *)getElem(btNode->child,i);
		// 复制到分裂的节点中去
		insert(u->child,temp);
	}
	// 分裂关键码 从S + 1开始 
	for(i = s + 1;i < tree->_order;i++){
		e = getElem(btNode->keys,i);
		if(i != s)
			// 复制到分裂的节点中去
			insert(u->keys,e);
	}
	deleteRange(btNode->keys,s,tree->_order -1);
	deleteRange(btNode->child,s+1,tree->_order);
	//若u的孩子们非空，则
	for(i = 0;i<u->child->size;i++){
		temp = (BTNode *)getElem(u->child,i);
		if(temp)
			temp->parent = u; //令它们的父节点统一
	}
	p = btNode->parent;
	if(!p){
		p = newBTNode(NULL,tree->_order,(tree->_order - 1) * sizeof(int));
		tree->root = p;
		insert(p->keys,shangyi);
		u->parent = p;
		btNode->parent = p;
		insert(p->child,btNode);
		insert(p->child,u);
	} else {
		i = searchInChild(shangyi,p->keys);
		insert2(p->keys,shangyi,i+1);
		insert2(p->child,u,i+2);
		u->parent = p;
	}
	solveOverflow(p,tree);
}

void insertBtree(Elem e , BTree * tree){
	int r;
	BTNode * hot;
	BTNode * node = searchBtree(e,tree);
	hot = tree->hot;
	if(node) 
		return; // 如果存在插入失败
	if(!hot) {
		// 空树首先构造一个父节点
		tree->root = newBTNode(NULL,tree->_order,(tree->_order - 1) * sizeof(int));
		insert(tree->root->keys,e);
		insert(tree->root->child,NULL);
		insert(tree->root->child,NULL);
		return;
	}

	r = searchInChild(e,hot->keys);//在节点_hot的有序关键码向量中查找合适的插入位置
	insert2(hot->keys,e,r+1); //将新关键码插至对应的位置
	insert2(hot->child,NULL,r+2);
	tree->size++;//更新全树规模
	solveOverflow(hot,tree); //如有必要，需做分裂
}

void removeBtree(Elem e , BTree * tree){
	int r;
	BTNode * u;
	BTNode * v = searchBtree(e,tree);
	if(!v) return;//不过不存在结束
	r = searchInChild(e,v->keys); // 获得e在v中的秩
	// 如果v不是叶子节点，为了保证树的关系 不能直接删除 
	// 需要不断在右子树中向左查找找到e的后继 然后互换节点后再删除
	if(v->child->elem[0]){
		u = (BTNode *)getElem(v->child,r+1);
		while(u->child->elem[0])
			u = (BTNode *)u->child->elem[0];
		// 交换位置
		v->keys->elem[r] = u->keys->elem[0];
		v = u;
		r = 0;
	}
	// 此时v在叶子节点，删除的就是叶子节点 之前的后继节点已经上溢
	deleteSingle(v->keys,r);
	deleteSingle(v->child,r+1);
	tree->size--;
	solveUnderflow(v,tree);//如有必要，需做旋转和合并
}

//关键码删除后若节点下溢，则做节点旋转或合并处理
void solveUnderflow(BTNode * btNode,BTree * tree){
	int r = 0;
	BTNode * p , * ls , * rs;
	if ((tree->_order + 1) / 2 <= btNode->child->size) 
		return; //递归基：当前节点并未下溢
	p = btNode->parent;
	if(!p){ //递归基：已到根节点，没有孩子的下限
		// 如果树根已经不包含关键码 却有（唯一的）非空孩子，则
		if(!btNode->keys->size && btNode->child->elem[0]){
			tree->root = btNode->child->elem[0];
			tree->root->parent = NULL;
			deleteSingle(btNode->child,0);
		} //整树高度降低一层 
		return;
	}
	//确定btNode是p的第r个孩子
	while( p->child->elem[r] != btNode ) 
		r++;
	//printf("%d \n",r);
	// 情况1：向左兄弟借关键码
	// 若v不是p的第一个孩子，则
	if (0 < r) { 
		ls = p->child->elem[r-1];//左兄弟必存在
		//若该兄弟足够“胖”，则
		if ((tree->_order + 1) / 2 < ls->child->size){
			//p借出一个关键码给btNode（作为最小关键码)
			insert2(btNode->keys ,p->keys->elem[r-1] ,0);
			//ls的最大关键码转入p
			p->keys->elem[r-1] = ls->keys->elem[ls->keys->size-1];
			//ls的最右侧孩子给btNode
			insert2(btNode->child ,ls->child->elem[ls->child->size-1] ,0);
			// 删除ls 的最大关键码和孩子
			deleteSingle(ls->keys,ls->keys->size-1);
			deleteSingle(ls->child,ls->child->size-1);
			//同时ls的最右侧孩子过继给btNode ,作为btNode的最左侧孩子
			if(btNode->child->elem[0])
				((BTNode *)btNode->child->elem[0])->parent = btNode;
			return; //至此，通过右旋已完成当前层（以及所有层）的下溢处理
		}
	} //至此，左兄弟要么为空，要么太“瘦”
	// 情况2：向右兄弟借关键码
	if (p->child->size - 1 > r) { //若v不是p的最后一个孩子，则
		rs = p->child->elem[r+1];//右兄弟必存在
		if ((tree->_order + 1) / 2 < rs->child->size) { //若该兄弟足够“胖”，则
			//p借出一个关键码给btNode（作为最大关键码）
			insert2(btNode->keys ,p->keys->elem[r] ,btNode->keys->size); 
			//rs的最小关键码转入p
			p->keys->elem[r] = rs->keys->elem[0];
			//rs的最左侧孩子给btNode
			insert2(btNode->child ,rs->child->elem[0] ,btNode->child->size);
			// 删除rs 的最小关键码和孩子
			deleteSingle(rs->keys,0);
			deleteSingle(rs->child,0);
			//同时rs的最左侧孩子过继给btNode
			if(btNode->child->elem[btNode->child->size - 1])
				((BTNode *)btNode->child->elem[btNode->child->size - 1])->parent = btNode;
			return ;//至此，通过左旋已完成当前层（以及所有层）的下溢处理
		}
	}//至此，右兄弟要么为空，要么太“瘦”
	// 情况3：左、右兄弟要么为空（但不可能同时），要么都太“瘦”——合并
	if (0 < r) { //与左兄弟合并
		ls = p->child->elem[r-1];//左兄弟必存在
		//p的第r - 1个关键码转入ls，btNode不再是p的第r个孩子
		insert(ls->keys,p->keys->elem[r-1]);
		deleteSingle(p->keys,r-1);
		deleteSingle(p->child,r);
		// ls 与 btNode合并
		// v的最左侧孩子过继给ls做最右侧孩子 孩子比关键节点多一个 所以先合并一个孩子
		insert(ls->child,btNode->child->elem[0]);
		if(ls->child->elem[ls->child->size-1])
			((BTNode *)ls->child->elem[ls->child->size-1])->parent = ls;
		deleteSingle(btNode->child,0); // 删除第一个孩子
		while(btNode->keys->size){ // btNode剩余的关键码和孩子，依次转入ls
			insert(ls->keys,btNode->keys->elem[0]);
			deleteSingle(btNode->keys,0);			
			insert(ls->child,btNode->child->elem[0]);
			deleteSingle(btNode->child,0);
			if(ls->child->elem[ls->child->size-1])
				((BTNode *)ls->child->elem[ls->child->size-1])->parent = ls;
		}
		free(btNode);//释放btNode
	} else { //与右兄弟合并
		rs = p->child->elem[r+1];//右兄弟必存在
		//p的第r个关键码转入rs，btNode不再是p的第r个孩子 放入第一个节点
		insert2(rs->keys,p->keys->elem[r],0);
		deleteSingle(p->keys,r);
		deleteSingle(p->child,r);
		// rs 与 btNode合并
		insert2(rs->child,btNode->child->elem[btNode->child->size-1],0);
		if(rs->child->elem[0])
			((BTNode *)rs->child->elem[0])->parent = rs;
		deleteSingle(btNode->child,btNode->child->size-1); // 删除最后一个个孩子
		while(btNode->keys->size){ // btNode剩余的关键码和孩子，依次转入rs
			insert2(rs->keys,btNode->keys->elem[btNode->keys->size-1],0);
			deleteSingle(btNode->keys,btNode->keys->size-1);			
			insert2(rs->child,btNode->child->elem[btNode->child->size-1],0);
			deleteSingle(btNode->child,btNode->child->size-1);
			if(rs->child->elem[0])
				((BTNode *)rs->child->elem[0])->parent = rs;
		}
		free(btNode);//释放btNode
	}
	solveUnderflow(p,tree);
}

int geiBTreeHigh(BTree * tree){
	int high = 0;
	BTNode * node = tree->root;
	while(node){
		node = node->child->elem[0];
		high++;
	}
	return high;
}

void printBTree(BTree * tree){
	int i;
	Queue * qu = initQueue();
	BTNode * node = tree->root;
	enqueue(node,qu); // 首节点入队
	while(!emptyQueue(qu)){
		node = dequeue(qu);
		if(node){
			printVector(node->keys);
			printf("\n");
			for(i = 0;i < node->child->size;i++)
				enqueue(getElem(node->child,i),qu);		
		}
	}

}