#ifndef _QUEUE_H
#define _QUEUE_H

#include "List.h"
#define FALSE 0
#define TRUE  1
typedef struct _queue{
	List * elem;
	int size;
} Queue;

// 初始化队列
Queue * initQueue();
// 入队
void enqueue(ElemType x , Queue * queue);
// 出队
ElemType dequeue(Queue * queue);
// 是否为空
int emptyQueue(Queue * queue);
void clearQueue(Queue * queue);

#endif
