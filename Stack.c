#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack * initStack(){
	Stack * stack = (Stack *)malloc(sizeof(Stack));
	stack->size = 0;
	stack->elem = initList();
	return stack;
}

void push(ElemType x , Stack * stack){
	insertBefore(x,stack->elem);
	stack->size++;
}

ElemType pop(Stack * stack){
	ElemType x = NULL; 
	ListNode * node;
	if(stack->size > 0){
		node = getFirst(stack->elem);
		x = node->data;
		deleteListNode(node);
		stack->size--;
	}
	return x;
}

ElemType top(Stack * stack){
	return getFirst(stack->elem)->data;
}

int empty(Stack * stack){
	return (stack->size == 0) ? TRUE : FALSE;
}

void clearStack(Stack * stack){
	clearList(stack->elem);
	stack->size = 0;
}