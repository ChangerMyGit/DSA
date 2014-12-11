#include <stdio.h>
#include <stdlib.h>
#define swap_t(t , x, y) {t temp = x; x = y; y = temp;}
void quickSort(int * elem , int lo , int hi);
int partition(int * elem , int lo , int hi);
// ����ȡ��
int getMiddle(int * elem , int lo , int hi);
void swap_elem(int * x , int * y);
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

//��㹹���㷨��ͨ������Ԫ��λ�ù�������[lo, hi]����㣬����������
int partition(int * elem , int lo , int hi){
	int pivot;
	//int pivot = elem[lo]; // Ĭ����Ԫ��Ϊ���
	int swap_index = getMiddle(elem,lo,hi); // ����ȡ�� 
	swap_t(int ,elem[lo],elem[swap_index]); // Ȼ�����Ԫ�ؽ���
	pivot = elem[lo];
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

int getMiddle(int * elem , int lo , int hi){
	int first = elem[lo];
	int middle = elem[(lo + hi)/2];
	int last = elem[hi];
	if((first >= middle && first <= last) || (first >= last && first <= middle))
		return lo;
	else if((middle >= first && middle <= last) || (middle >= last && middle <= first))
		return (lo + hi)/2;
	else 
		return hi;
}

void swap_elem(int * x , int * y){
	int temp = *x;
	*x = *y;
	*y = temp;
}