#include "MyString.h"
#include <string.h>

// ����ƥ�䷨ ʱ�临�Ӷ� O��N * M��
int matchString(char * p , char * t){
	int i = 0 , j = 0;
	size_t n = strlen(p);
	size_t m = strlen(t);
	while(i < m && j < n){
		if(p[j] == t[i]){
			j++;i++;
		} else { // p ����Ϊ0 t ����
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