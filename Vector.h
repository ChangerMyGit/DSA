#ifndef _VECTOR_H
#define _VECTOR_H

#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0
typedef  void * Elem;

typedef struct _vec{
	int size;
	Elem * elem;
	int capacity;
} Vector;

// ��ʼ��
Vector * initVector(int capacity);
// ����
void expand(Vector * vec);
// ����
void insert(Vector * vec , Elem e);
// ���� 
void insert2(Vector * vec , Elem e,unsigned int i);
// ɾ�� ��Χɾ��
void deleteRange(Vector * vec,unsigned int lo,unsigned int high);
// ����ɾ��
void deleteSingle(Vector * vec,unsigned int i);
// ����
int find(Vector * vec,unsigned int i);
// ȥ��
void reduplicate(Vector * vec);
// �鿴�Ƿ�����
int disortered(Vector * vec);
// ����������ȥ�� ��ʱ�临�Ӷ�ΪO(n)
int uniquify(Vector * vec);
// ����
void sort(Vector * vec);
// ���ֲ��� lo = 0 hi = length
int binSearch(Vector * vec,int lo,int hi,Elem x);
// ���ֲ��� lo = 0 hi = length-1
int binSearch2(Vector * vec,int lo,int hi,Elem x);
// ���ֲ��� ������ҷ�֧��ƽ�������
int binSearch3(Vector * vec,Elem x);
// 쳲���������
int fibonacciSearch(Vector * vec,Elem x);
//����쳲���������  
void fibonacci(int *f);   
// �滻
void vec_swap(Elem * x , Elem * y);
// ð������Ľ���
void bubbleSort(Vector * vec);
int bubble(Vector * vec,int lo,int hi);
// ------------------------------
// �����Ѿ�������������� ��¼���λ�ã��´α��������ⲿ������
void bubbleSort2(Vector * vec);
int bubble2(Vector * vec,int lo,int hi);

// ��·�鲢���� [lo,mi] , [mi+1 , hi]
void merge(Vector * vec,int lo , int hi);
void mergeSort(Vector * vec,int lo ,int mi, int hi);
void printVector(Vector * vec);

#endif