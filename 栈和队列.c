#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// ����ת�� ʹ��ջ�����
void convert(Stack * stack , unsigned n , int base);
int main(){
	int i;
	Stack * stack = initStack();
/**
    for(i = 0 ; i< 10 ;i++)
		push(i,stack);
	while(stack->size > 0)
		printf("%d ",pop(stack));
	printf("\n");
**/	
	convert(stack,10,16);
	return 0;
}

// n ԭ�� base �ǽ����� ���֧��16����
void convert(Stack * stack , unsigned n , int base){
	static char digit[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	while(n){
		push(digit[n % base],stack);
		n = n/base;
	}
	while(stack->size > 0)
		printf("%c",pop(stack));
	printf("\n");
}