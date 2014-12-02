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
} PQ_ComplHeap; 


PQ_ComplHeap * initPQ(int size);

// 按照比较器确定的优先级次序插入词条
void insertPQ(Elem e , PQ_ComplHeap * pq);
// 取出优先级最高的词条
Elem getMax(PQ_ComplHeap * pq);
// 删除优先级最高的词条
Elem delMax(PQ_ComplHeap * pq);
// 上溢
void percolateUp(int n , PQ_ComplHeap * pq);
#endif