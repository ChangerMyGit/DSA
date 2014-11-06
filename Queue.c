#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue * initQueue(){
	Queue * queue = (Queue *)malloc(sizeof(Queue));
	queue->elem = initList();
	queue->size = 0;
	return queue;
}

// 入队插入队尾
void enqueue(ElemType x , Queue * queue)
{
	inserLast(x,queue->elem);
	queue->size++;
}

// 获取队首元素，删除该元素
ElemType dequeue(Queue * queue){
	ElemType x = getFirst(queue->elem)->data;
	deleteListNode(getFirst(queue->elem));
	return x;
}

void clearQueue(Queue * queue){
	clearList(queue->elem);
	queue->size = 0;
}

int emptyQueue(Queue * queue){
	return (queue->size == 0)?TRUE:FALSE;
}