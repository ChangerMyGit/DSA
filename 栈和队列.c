#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Queue.h"

// ����ת�� ʹ��ջ�����
void convert(Stack * stack , unsigned n , int base);
// ����ƥ��
int paren(Stack * stack,char * str);
// ��ȡ�����ŵ�����
int getBracketsIndex(char c , char * s);
// �Ƿ���������
int isLeftBrackers(char c , char * sl);
// �Ƿ���������
int isRightBrackers(char c , char * sr);
// ��������ƥ��
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
		printf("ƥ��ɹ�!\n");
	else
		printf("ƥ��ʧ��!\n");
**/	

	for(i = 1;i<=10;i++)
		enqueue(i,queue);
	for(i = 1;i<=10;i++)
		printf("%d ",dequeue(queue));
	printf("\n");
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

int paren(Stack * stack,char * str){
	char c , t;
	static char leftStr[] = {'(','[','{'};
	static char rightStr[] = {')',']','}'};
	while((c = *str++)){
		if(isLeftBrackers(c,leftStr)) 
			push(c,stack);// ��������ջ
		else if(isRightBrackers(c,rightStr)){ // ������ ջΪ�ղ�ƥ�� �����ջ
			if(stack->size == 0)
				return FALSE;
			else if(!brackersMatch(pop(stack),c,leftStr,rightStr)) // ���Ų�ƥ��
				return FALSE;
	 	}
	}
	// ջΪ�� ��ȫƥ�� ����ƥ��ʧ��
	return (stack->size == 0)?TRUE:FALSE;
}

// ��ȡ��������
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

// �Ƿ���������
int isLeftBrackers(char c , char * sl){
	for(;*sl;sl++){
		if(c == *sl)
			return TRUE;
	}
	return FALSE;   
}

// �Ƿ���������
int isRightBrackers(char c , char * sr){
	for(;*sr;sr++){
		if(c == *sr)
			return TRUE;
	}
	return FALSE;   
}