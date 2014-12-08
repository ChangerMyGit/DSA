#include "MyString.h"
#include <string.h>
#include <stdlib.h>

// 蛮力匹配法 时间复杂度 O（N * M）
int matchString(char * p , char * t){
	int i = 0 , j = 0;
	size_t n = strlen(p);
	size_t m = strlen(t);
	while(i < m && j < n){
		if(p[j] == t[i]){
			j++;i++;
		} else { // p 重置为0 t 回退
			i -= j - 1;
			j = 0;
		}
	}
	return (i == m) ? -1 : i - j;
}

int matchString2(char * p , char * t){
	int i , j , k;
	for(i = 0 ; i < strlen(t) ; i++){
		k = i;
		for(j = 0 ; j < strlen(p) ; j++){
			if(p[j] == t[k])
				k++;
			else 
				break;
		}
		if(j == strlen(p)) 
			return i;
	}	
	return -1;
}

int * buildNext(char * p){
	int j = 0;
	size_t m = strlen(p);
	int * n = (int *)malloc(m * sizeof(int));
	int t = n[0] = -1;
	while(j < m - 1){
		if(t < 0 || p[j] == p[t]){
			j++;
			t++;
			n[j] = (p[j] != p[t])?t:n[t]; // 改进版 对于重复的元素 不再重复比较
		} else {
			t = n[t];
		}
	}
	return n;
}

int kmpMatch(char * p , char * t){
    int i = 0 , j = 0;
	int * next = buildNext(p);
	int m = strlen(p);
	int n = strlen(t);
	while(i < n && j < m){
		if( j < 0 || t[i] == p[j]){
		     i++;j++ ;
		} else 
			j = next[j];
	}
	free(next);
	return i - j;
}