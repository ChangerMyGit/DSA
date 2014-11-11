#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"

Vector * initVector(int capacity){
	Vector * vec = (Vector *)malloc(sizeof(Vector));
	vec->size = 0;
	vec->capacity = capacity;
	vec->elem = (Elem *)malloc(capacity);
	return vec;
}

void expand(Vector * vec){
	vec->elem = (int *)realloc(vec->elem , vec->capacity  << 1);
	vec->capacity <<=1; 
}

void insert(Vector * vec , Elem e){
	if(vec->size == vec->capacity / sizeof(int)){
		expand(vec);
	}  
	vec->elem[(vec->size)++] = e;
}

void insert2(Vector * vec , Elem e,int i){
	int len = vec->size;
	// 整体后移
	if(i>=0 && i< vec->size){
		while(len > i){
			vec->elem[len] = vec->elem[len-1];
			len --;
		}
		vec->elem[i] = e;
		vec->size++;
	} else {
		insert(vec,e);
	}
}

void deleteRange(Vector * vec,unsigned int lo,unsigned int high){
	if(lo == high);
	if(lo <= high && lo < vec->size && high < vec->size){
		high++;// 移到删除的范围外 [lo,high] -> [lo,high);
		while(high < vec->size){
			vec->elem[lo++] = vec->elem[high++];
		}
		vec->size = vec->size - (high - lo);
	}
}

void deleteSingle(Vector * vec,unsigned int i){
	deleteRange(vec,i,i);
}

int find(Vector * vec,unsigned int i){
	if(i<vec->size)
		return vec->elem[i];
	return -1;
}

void reduplicate(Vector * vec){
	// 默认从1开始 遍历i之前的集合 如果发现有和i重复项 删除i，然后取i+1 再次比较
	int j, i = 1;
	while(i<vec->size){
		for(j=0;j<i;j++){
			// 如果想等 删除i
			if(vec->elem[j] == vec->elem[i])
				deleteSingle(vec,i);
		}
		i++;
	}
}

int disortered(Vector * vec){
	int n = 0 ,i;
	for(i = 0;i<vec->size;i++){
		n += (vec->elem[i] > vec->elem[i+1]);
	}
	return n;
}

// 对有序向量去重 ，时间复杂度为O(n)
int uniquify(Vector * vec){
	int i,j;
	for(i = 0 , j = 1;j<vec->size;j++){
		if(vec->elem[i] != vec->elem[j]){
		    vec->elem[++i] = vec->elem[j]; // 复制到i之后的元素 然后i增1
		}
	}
	vec->size = ++i;
	return j - i +1;
}

void vec_swap(Elem * x , Elem * y){
	Elem temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void sort(Vector * vec){
	int i , j;
	for(i = vec->size;i>0;i--)
		for(j = 1; j < i ; j++){
			if(vec->elem[j-1] >  vec->elem[j])
				vec_swap(&vec->elem[j-1],&vec->elem[j]);
		}
}

// lo = 0 hi = length
int binSearch(Vector * vec,int lo,int hi,Elem x){
	int mi;
	while(lo < hi){
		mi = (lo + hi) >> 1;
		if(vec->elem[mi] > x) hi = mi;
		else if(vec->elem[mi] < x) lo = mi + 1;
		else return mi;
	}
	return -1;
}

// lo = 0 hi = length-1
int binSearch2(Vector * vec,int lo,int hi,Elem x){
	int mi;
	while(lo <= hi){
		mi = (lo + hi) >> 1;
		if(vec->elem[mi] > x) hi = mi-1;
		else if(vec->elem[mi] < x) lo = mi + 1;
		else return mi;
	}
	return -1;
}

// 二分查找 解决左右分支不平衡的问题
// 每次只有两个分支 x < a[mi] [lo,mi) a[mi] <= x [mi+1 , hi)
int binSearch3(Vector * vec,Elem x){
	int lo = 0 , mi , hi = vec->size;
	if(x > vec->elem[hi-1] || x <  vec->elem[lo]) 
	    return (x > vec->elem[hi-1]) ? hi : lo-1;
	while(lo < hi){
		mi = (lo + hi) >> 1;
		(x < vec->elem[mi]) ? (hi = mi):(lo = mi + 1);
	}
	return --lo; // 最终元素是左侧区间的最后一个元素
}

void fibonacci(int *f){
	int i;
	f[0] = 0;
	f[1] = 1;
	for(i = 2 ;i < MAX_SIZE; i++){
		f[i] = f[i-1] + f[i-2];
	}
}

int fibonacciSearch(Vector * vec,Elem x){
	int lo = 0 ,hi = vec->size ,mi , k = 0;
	int f[MAX_SIZE];
    fibonacci(f);
	while(vec->size > f[k]-1)
		k++;
	while(lo < hi){
	    mi = lo + f[k-1] - 1;
		if(vec->elem[mi] > x){
			hi = mi;
			k -=1;
		} else if(vec->elem[mi] < x){
		    lo = mi + 1;
			k -=2;
		} else 
			return mi;
	}
	return -1;
}

// 冒泡排序改进版
void bubbleSort(Vector * vec){
	int hi = vec->size;
	// 避免向右移除 使用lo 和 lo - 1 比较 所以lo初始化为1
	while(!bubble(vec,1,hi--)); // 逐行扫描直至全续
}

int bubble(Vector * vec,int lo,int hi){
	int sorted = TRUE;
	for(;lo < hi; lo++){
		if(vec->elem[lo-1] > vec->elem[lo]){
			vec_swap(&vec->elem[lo-1],&vec->elem[lo]);
			sorted = FALSE;
		}
	}
	return sorted;
}

void bubbleSort2(Vector * vec){
   int hi = vec->size;
   while ((hi = bubble2(vec,1,hi)) > 1)
	   ;
}

int bubble2(Vector * vec,int lo,int hi){
	int last = lo;
	for(;lo < hi; lo++){
		if(vec->elem[lo-1] > vec->elem[lo]){
			vec_swap(&vec->elem[lo-1],&vec->elem[lo]);
			last = lo;
		}
	}
	return last;
}

void merge(Vector * vec,int lo , int hi){
	int mi;
	if((hi - lo) <=1){
		if(vec->elem[lo] > vec->elem[hi])
			vec_swap(&vec->elem[lo],&vec->elem[hi]);
	} else {
		mi = (lo + hi) >> 1;
	    merge(vec,lo,mi);
		merge(vec,mi+1,hi);
		mergeSort(vec,lo,mi,hi);
	}
}

// 声明一块左区间 B [lo,mi] 供交换使用 右区间C[mi+1,hi]
void mergeSort(Vector * vec,int lo ,int mi, int hi){
	int i,j,k,lb,lc,bi;
	Elem * b , * c;
	lb = (mi - lo) + 1;
	lc = (hi - (mi + 1)) + 1;
	b = (Elem *)malloc(lb * sizeof(int));
	for(bi = 0,i = lo;bi < lb;bi++,i++)
		b[bi] = vec->elem[i];
	c = &vec->elem[mi + 1];
	for(i = lo,j = 0,k = 0;(j < lb || k < lc);){
		if((b[j] <= c[k] && j < lb) || k == lc){
			vec->elem[i++] = b[j++];
			continue;
		}
		if((c[k] <= b[j] &&  k < lc) || j == lb){
			vec->elem[i++] = c[k++];
			continue;
		}
	}
    free(b);
}

void printVector(Vector * vec){
	int i = 0;
	for(;i<vec->size;i++)
		printf("%d ",vec->elem[i]);
}

Elem getElem(Vector * vec ,int i){
	Elem e = vec->elem[i];
	return e;
}
