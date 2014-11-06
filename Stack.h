/**
 **
   使用列表来实现栈
   典型应用场合：1 逆序输出 2 递归嵌套 3 延迟缓冲 4 栈式计算
**/
#include "List.h"
#define FALSE 0
#define TRUE  1
typedef struct _stack{
	List * elem;
	int size;
} Stack;

// 初始化栈
Stack * initStack();
// 出栈
ElemType pop(Stack * stack);
// 入栈
void push(ElemType x , Stack * stack);
// 获得栈顶元素
ElemType top(Stack * stack);
// 是否为空
int empty(Stack * stack);
void clearStack(Stack * stack);