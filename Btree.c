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
	// ����M������
	node->child = initVector(order * sizeof(BTNode *));
	// ����M-1���ؼ���
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
			return v; // ���ؽڵ�
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
		return; //�ݹ������ǰ�ڵ㲢δ����
	// ��㣨��ʱӦ��_order = key.size() = child.size() - 1��
	s = tree->_order/2;
	// ����ڵ�
	shangyi = getElem(btNode->keys,s);
	// �����µĽڵ�
	u = newBTNode(NULL,s, (s - 1) * sizeof(int));
	// ���Ѻ��ӹ�ϵ ��S+1 ��ʼ �� order ����
	for(i = s + 1;i <= tree->_order;i++){
		temp = (BTNode *)getElem(btNode->child,i);
		// ���Ƶ����ѵĽڵ���ȥ
		insert(u->child,temp);
	}
	// ���ѹؼ��� ��S + 1��ʼ 
	for(i = s + 1;i < tree->_order;i++){
		e = getElem(btNode->keys,i);
		if(i != s)
			// ���Ƶ����ѵĽڵ���ȥ
			insert(u->keys,e);
	}
	deleteRange(btNode->keys,s,tree->_order -1);
	deleteRange(btNode->child,s+1,tree->_order);
	//��u�ĺ����Ƿǿգ���
	for(i = 0;i<u->child->size;i++){
		temp = (BTNode *)getElem(u->child,i);
		if(temp)
			temp->parent = u; //�����ǵĸ��ڵ�ͳһ
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
		return; // ������ڲ���ʧ��
	if(!hot) {
		// �������ȹ���һ�����ڵ�
		tree->root = newBTNode(NULL,tree->_order,(tree->_order - 1) * sizeof(int));
		insert(tree->root->keys,e);
		insert(tree->root->child,NULL);
		insert(tree->root->child,NULL);
		return;
	}

	r = searchInChild(e,hot->keys);//�ڽڵ�_hot������ؼ��������в��Һ��ʵĲ���λ��
	insert2(hot->keys,e,r+1); //���¹ؼ��������Ӧ��λ��
	insert2(hot->child,NULL,r+2);
	tree->size++;//����ȫ����ģ
	solveOverflow(hot,tree); //���б�Ҫ����������
}

void removeBtree(Elem e , BTree * tree){
	int r;
	BTNode * u;
	BTNode * v = searchBtree(e,tree);
	if(!v) return;//���������ڽ���
	r = searchInChild(e,v->keys); // ���e��v�е���
	// ���v����Ҷ�ӽڵ㣬Ϊ�˱�֤���Ĺ�ϵ ����ֱ��ɾ�� 
	// ��Ҫ����������������������ҵ�e�ĺ�� Ȼ�󻥻��ڵ����ɾ��
	if(v->child->elem[0]){
		u = (BTNode *)getElem(v->child,r+1);
		while(u->child->elem[0])
			u = (BTNode *)u->child->elem[0];
		// ����λ��
		v->keys->elem[r] = u->keys->elem[0];
		v = u;
		r = 0;
	}
	// ��ʱv��Ҷ�ӽڵ㣬ɾ���ľ���Ҷ�ӽڵ� ֮ǰ�ĺ�̽ڵ��Ѿ�����
	deleteSingle(v->keys,r);
	deleteSingle(v->child,r+1);
	tree->size--;
	solveUnderflow(v,tree);//���б�Ҫ��������ת�ͺϲ�
}

//�ؼ���ɾ�������ڵ����磬�����ڵ���ת��ϲ�����
void solveUnderflow(BTNode * btNode,BTree * tree){
	int r = 0;
	BTNode * p , * ls , * rs;
	if ((tree->_order + 1) / 2 <= btNode->child->size) 
		return; //�ݹ������ǰ�ڵ㲢δ����
	p = btNode->parent;
	if(!p){ //�ݹ�����ѵ����ڵ㣬û�к��ӵ�����
		// ��������Ѿ��������ؼ��� ȴ�У�Ψһ�ģ��ǿպ��ӣ���
		if(!btNode->keys->size && btNode->child->elem[0]){
			tree->root = btNode->child->elem[0];
			tree->root->parent = NULL;
			deleteSingle(btNode->child,0);
		} //�����߶Ƚ���һ�� 
		return;
	}
	//ȷ��btNode��p�ĵ�r������
	while( p->child->elem[r] != btNode ) 
		r++;
	//printf("%d \n",r);
	// ���1�������ֵܽ�ؼ���
	// ��v����p�ĵ�һ�����ӣ���
	if (0 < r) { 
		ls = p->child->elem[r-1];//���ֵܱش���
		//�����ֵ��㹻���֡�����
		if ((tree->_order + 1) / 2 < ls->child->size){
			//p���һ���ؼ����btNode����Ϊ��С�ؼ���)
			insert2(btNode->keys ,p->keys->elem[r-1] ,0);
			//ls�����ؼ���ת��p
			p->keys->elem[r-1] = ls->keys->elem[ls->keys->size-1];
			//ls�����Ҳຢ�Ӹ�btNode
			insert2(btNode->child ,ls->child->elem[ls->child->size-1] ,0);
			// ɾ��ls �����ؼ���ͺ���
			deleteSingle(ls->keys,ls->keys->size-1);
			deleteSingle(ls->child,ls->child->size-1);
			//ͬʱls�����Ҳຢ�ӹ��̸�btNode ,��ΪbtNode������ຢ��
			if(btNode->child->elem[0])
				((BTNode *)btNode->child->elem[0])->parent = btNode;
			return; //���ˣ�ͨ����������ɵ�ǰ�㣨�Լ����в㣩�����紦��
		}
	} //���ˣ����ֵ�ҪôΪ�գ�Ҫô̫���ݡ�
	// ���2�������ֵܽ�ؼ���
	if (p->child->size - 1 > r) { //��v����p�����һ�����ӣ���
		rs = p->child->elem[r+1];//���ֵܱش���
		if ((tree->_order + 1) / 2 < rs->child->size) { //�����ֵ��㹻���֡�����
			//p���һ���ؼ����btNode����Ϊ���ؼ��룩
			insert2(btNode->keys ,p->keys->elem[r] ,btNode->keys->size); 
			//rs����С�ؼ���ת��p
			p->keys->elem[r] = rs->keys->elem[0];
			//rs������ຢ�Ӹ�btNode
			insert2(btNode->child ,rs->child->elem[0] ,btNode->child->size);
			// ɾ��rs ����С�ؼ���ͺ���
			deleteSingle(rs->keys,0);
			deleteSingle(rs->child,0);
			//ͬʱrs������ຢ�ӹ��̸�btNode
			if(btNode->child->elem[btNode->child->size - 1])
				((BTNode *)btNode->child->elem[btNode->child->size - 1])->parent = btNode;
			return ;//���ˣ�ͨ����������ɵ�ǰ�㣨�Լ����в㣩�����紦��
		}
	}//���ˣ����ֵ�ҪôΪ�գ�Ҫô̫���ݡ�
	// ���3�������ֵ�ҪôΪ�գ���������ͬʱ����Ҫô��̫���ݡ������ϲ�
	if (0 < r) { //�����ֵܺϲ�
		ls = p->child->elem[r-1];//���ֵܱش���
		//p�ĵ�r - 1���ؼ���ת��ls��btNode������p�ĵ�r������
		insert(ls->keys,p->keys->elem[r-1]);
		deleteSingle(p->keys,r-1);
		deleteSingle(p->child,r);
		// ls �� btNode�ϲ�
		// v������ຢ�ӹ��̸�ls�����Ҳຢ�� ���ӱȹؼ��ڵ��һ�� �����Ⱥϲ�һ������
		insert(ls->child,btNode->child->elem[0]);
		if(ls->child->elem[ls->child->size-1])
			((BTNode *)ls->child->elem[ls->child->size-1])->parent = ls;
		deleteSingle(btNode->child,0); // ɾ����һ������
		while(btNode->keys->size){ // btNodeʣ��Ĺؼ���ͺ��ӣ�����ת��ls
			insert(ls->keys,btNode->keys->elem[0]);
			deleteSingle(btNode->keys,0);			
			insert(ls->child,btNode->child->elem[0]);
			deleteSingle(btNode->child,0);
			if(ls->child->elem[ls->child->size-1])
				((BTNode *)ls->child->elem[ls->child->size-1])->parent = ls;
		}
		free(btNode);//�ͷ�btNode
	} else { //�����ֵܺϲ�
		rs = p->child->elem[r+1];//���ֵܱش���
		//p�ĵ�r���ؼ���ת��rs��btNode������p�ĵ�r������ �����һ���ڵ�
		insert2(rs->keys,p->keys->elem[r],0);
		deleteSingle(p->keys,r);
		deleteSingle(p->child,r);
		// rs �� btNode�ϲ�
		insert2(rs->child,btNode->child->elem[btNode->child->size-1],0);
		if(rs->child->elem[0])
			((BTNode *)rs->child->elem[0])->parent = rs;
		deleteSingle(btNode->child,btNode->child->size-1); // ɾ�����һ��������
		while(btNode->keys->size){ // btNodeʣ��Ĺؼ���ͺ��ӣ�����ת��rs
			insert2(rs->keys,btNode->keys->elem[btNode->keys->size-1],0);
			deleteSingle(btNode->keys,btNode->keys->size-1);			
			insert2(rs->child,btNode->child->elem[btNode->child->size-1],0);
			deleteSingle(btNode->child,btNode->child->size-1);
			if(rs->child->elem[0])
				((BTNode *)rs->child->elem[0])->parent = rs;
		}
		free(btNode);//�ͷ�btNode
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
	enqueue(node,qu); // �׽ڵ����
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