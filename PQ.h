//优先队列
/**
使用完全二叉堆实现
二叉堆有两种：最大堆和最小堆。
最大堆：父结点的键值总是大于或等于任何一个子节点的键值；
最小堆：父结点的键值总是小于或等于任何一个子节点的键值。
**/
#ifndef _PQ_H
#define _PQ_H
#include "Vector.h"

typedef struct _pq{
	Vector * vector;
	int size;
} PQ_ComplHeap; 


PQ_ComplHeap * initPQ(int size);

// 按照比较器确定的优先级次序插入词条
void insertPQ(Elem e , PQ_ComplHeap * pq);
void insertPQ2(Elem e , PQ_ComplHeap * pq);
// 取出优先级最高的词条
Elem getMaxPQ(PQ_ComplHeap * pq);
// 删除优先级最高的词条
Elem delMax(PQ_ComplHeap * pq);
// 上溢
void percolateUp(int n , PQ_ComplHeap * pq);
void percolateUp2(int n , PQ_ComplHeap * pq);
// 下溢
void percolateDown(int n , PQ_ComplHeap * pq);
/*父子（至多）三者中的大者*/ 
int ProperParent(int n , PQ_ComplHeap * pq);
// 构造优先队列 ① 蛮力法 ② 使用下虑
void heapify(int n , PQ_ComplHeap * pq);
// 堆排序
void heapSort(PQ_ComplHeap * pq);
#endif