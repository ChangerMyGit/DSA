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

// 初始化
Vector * initVector(int capacity);
// 扩容
void expand(Vector * vec);
// 插入
void insert(Vector * vec , Elem e);
// 插入 
void insert2(Vector * vec , Elem e,unsigned int i);
// 删除 范围删除
void deleteRange(Vector * vec,unsigned int lo,unsigned int high);
// 单个删除
void deleteSingle(Vector * vec,unsigned int i);
// 查找
int find(Vector * vec,unsigned int i);
// 去重
void reduplicate(Vector * vec);
// 查看是否有序
int disortered(Vector * vec);
// 对有序向量去重 ，时间复杂度为O(n)
int uniquify(Vector * vec);
// 排序
void sort(Vector * vec);
// 二分查找 lo = 0 hi = length
int binSearch(Vector * vec,int lo,int hi,Elem x);
// 二分查找 lo = 0 hi = length-1
int binSearch2(Vector * vec,int lo,int hi,Elem x);
// 二分查找 解决左右分支不平衡的问题
int binSearch3(Vector * vec,Elem x);
// 斐波那契查找
int fibonacciSearch(Vector * vec,Elem x);
//构建斐波那契序列  
void fibonacci(int *f);   
// 替换
void vec_swap(Elem * x , Elem * y);
// 冒泡排序改进版
void bubbleSort(Vector * vec);
int bubble(Vector * vec,int lo,int hi);
// ------------------------------
// 对于已经部分排序的序列 记录其的位置，下次遍历跳过这部分序列
void bubbleSort2(Vector * vec);
int bubble2(Vector * vec,int lo,int hi);

// 二路归并排序 [lo,mi] , [mi+1 , hi]
void merge(Vector * vec,int lo , int hi);
void mergeSort(Vector * vec,int lo ,int mi, int hi);
void printVector(Vector * vec);

#endif