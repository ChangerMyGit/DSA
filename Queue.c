#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue * initQueue(){
	Queue * queue = (Queue *)malloc(sizeof(Queue));
	queue->elem = initList();
	queue->size = 0;
	return queue;
}

// ��Ӳ����β
void enqueue(ElemType x , Queue * queue)
{
	inserLast(x,queue->elem);
	queue->size++;
}

// ��ȡ����Ԫ�أ�ɾ����Ԫ��
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