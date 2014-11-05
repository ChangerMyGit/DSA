#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// 进制转换 使用栈来输出
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

// n 原数 base 是进制数 最大支持16进制
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