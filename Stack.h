/**
 **
   ʹ���б���ʵ��ջ
   ����Ӧ�ó��ϣ�1 ������� 2 �ݹ�Ƕ�� 3 �ӳٻ��� 4 ջʽ����
**/
#include "List.h"
#define FALSE 0
#define TRUE  1
typedef struct _stack{
	List * elem;
	int size;
} Stack;

// ��ʼ��ջ
Stack * initStack();
// ��ջ
ElemType pop(Stack * stack);
// ��ջ
void push(ElemType x , Stack * stack);
// ���ջ��Ԫ��
ElemType top(Stack * stack);
// �Ƿ�Ϊ��
int empty(Stack * stack);
void clearStack(Stack * stack);