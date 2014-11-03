#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void maopaoSort(int a[] , int n);
void selectSort(int a[] , int n);
void reverse(int a[],int lo,int hi);
void swap(int *a,int *b);
void Func(char str_arg[100]) ;
int binSearch(int a[],int lo,int hi,int x);
int main1(int argc,char *argv[]){
	int a[] = {2,4};
	//maopaoSort(a,6);
	//selectSort(a,7);
	//reverse(a,0,6);
	//for(i = 0;i<7;i++)
	// printf("%d ",a[i]);
	//printf("\n %d ",atoi(argv[1]) + atoi(argv[2]));
	//printf("%d\n",sizeof(str1));  
	printf("%d\n",binSearch(a,0,1,4));
	return 0;
}

/**
   int binSearch(int a[],int lo,int hi,int x){
	while(lo <= hi){
		int md = (lo + hi) >> 1 ;
		if(x < a[md]) hi = md-1;
		else if(x > a[md]) lo = md+1;
		else return md;
	}
	return -1;
}

**/

void maopaoSort(int a[] ,int n){
	int i ,j;
	for(i=n;i>0;i--)
		for(j=0;j<i;j++){
			if(a[j] > a[j+1])
				swap(&a[j],&a[j+1]);
		}	
}

void selectSort(int a[] , int n){
	int i,j,min;
	for(i = 0;i<n;i++){
		min = i;
		for(j = i+1 ;j<n;j++){
			if(a[min] > a[j])
				min = j;
		}
		if(min > i)
			swap(&a[min],&a[i]);
	}
}

// 分治法 递归逆序
void reverse(int a[],int lo,int hi){
	if(lo < hi){
		swap(&a[lo],&a[hi]);
		reverse(a,++lo,--hi);
	}
}

void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Func(char str_arg[100])  
{   
	// 传递的是一个指针变量
	printf("%d\n",sizeof(str_arg));  
} 