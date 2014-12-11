#include <stdio.h>
#include <stdlib.h>
void quickSort(int * elem , int lo , int hi);
int partition(int * elem , int lo , int hi);
int main(){
	int i;
	int elem[10] = {6,3,8,2,5,9,4,5,1,7};
	//int elem[10] = {1,2,3,4,5,6,7,8,9,10};
	quickSort(elem,0,sizeof(elem)/sizeof(int));
	for(i = 0; i < sizeof(elem)/sizeof(int) ; i++)
		printf("%d " , elem[i]);
	printf("\n");
	return 0;
}

//轴点构造算法：通过调整元素位置构造区间[lo, hi]的轴点，并返回其秩
int partition(int * elem , int lo , int hi){
	int pivot = elem[lo]; // 默认首元素为轴点
	while(lo < hi){
		while((lo < hi) && (elem[hi] >= pivot)) 
			hi--;
		if ( lo < hi ) 
			elem[lo++] = elem[hi];
		while(lo < hi && elem[lo] <= pivot) 
			lo++;
		if ( lo < hi ) 
			elem[hi--] = elem[lo];
	}
	elem[lo] = pivot;
	return lo;
}

void quickSort(int * elem , int lo , int hi){
	int mi;
	if(hi - lo < 2) return;
	mi = partition(elem,lo,hi-1);
	quickSort(elem,lo,mi);
	quickSort(elem,mi+1,hi);
}