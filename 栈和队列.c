#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Queue.h"

// 进制转换 使用栈来输出
void convert(Stack * stack , unsigned n , int base);
// 括号匹配
int paren(Stack * stack,char * str);
// 获取左括号的序列
int getBracketsIndex(char c , char * s);
// 是否是左括号
int isLeftBrackers(char c , char * sl);
// 是否是右括号
int isRightBrackers(char c , char * sr);
// 左右括号匹配
int brackersMatch(char lc , char rc ,char * sl , char * sr);
int main(){
	int i;
	char * c = "void * (*str[])(int x,int y){}";
	Stack * stack = initStack();
	Queue * queue = initQueue();
/**
    for(i = 0 ; i< 10 ;i++)
		push(i,stack);
	while(stack->size > 0)
		printf("%d ",pop(stack));
	printf("\n");

	//convert(stack,10,16);
	if(paren(stack,c))
		printf("匹配成功!\n");
	else
		printf("匹配失败!\n");
**/	

	for(i = 1;i<=10;i++)
		enqueue(i,queue);
	for(i = 1;i<=10;i++)
		printf("%d ",dequeue(queue));
	printf("\n");
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

int paren(Stack * stack,char * str){
	char c , t;
	static char leftStr[] = {'(','[','{'};
	static char rightStr[] = {')',']','}'};
	while((c = *str++)){
		if(isLeftBrackers(c,leftStr)) 
			push(c,stack);// 左括号入栈
		else if(isRightBrackers(c,rightStr)){ // 右括号 栈为空不匹配 否则出栈
			if(stack->size == 0)
				return FALSE;
			else if(!brackersMatch(pop(stack),c,leftStr,rightStr)) // 括号不匹配
				return FALSE;
	 	}
	}
	// 栈为空 完全匹配 否则匹配失败
	return (stack->size == 0)?TRUE:FALSE;
}

// 获取括号序列
int getBracketsIndex(char c , char * s){
	int i;
	for(i = 0;*s;s++,i++){
		if(c == *s)
			return i;
	}
	return -1;
}

int brackersMatch(char lc , char rc ,char * sl , char * sr){
    int i , j;
	i = getBracketsIndex(lc,sl);
	j = getBracketsIndex(rc,sr);
	return (i == j)?TRUE:FALSE;
}

// 是否是左括号
int isLeftBrackers(char c , char * sl){
	for(;*sl;sl++){
		if(c == *sl)
			return TRUE;
	}
	return FALSE;   
}

// 是否是右括号
int isRightBrackers(char c , char * sr){
	for(;*sr;sr++){
		if(c == *sr)
			return TRUE;
	}
	return FALSE;   
}