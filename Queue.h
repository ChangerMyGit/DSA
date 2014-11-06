#ifndef _QUEUE_H
#define _QUEUE_H

#include "List.h"
#define FALSE 0
#define TRUE  1
typedef struct _queue{
	List * elem;
	int size;
} Queue;

// ��ʼ������
Queue * initQueue();
// ���
void enqueue(ElemType x , Queue * queue);
// ����
ElemType dequeue(Queue * queue);
// �Ƿ�Ϊ��
int emptyQueue(Queue * queue);
void clearQueue(Queue * queue);

#endif
