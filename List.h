// 避免头文件重复引用
#ifndef _LIST_H
#define _LIST_H
// 通用类型
typedef  void * ElemType;
//列表节点模板类（以双向链表形式实现）
typedef struct _listNode{
	ElemType data;// 通用数据类型
	struct _listNode * pre; // 前驱 
	struct _listNode * succ; // 后继
	struct _list * list;
} ListNode;

typedef struct _list {
	int size;
	//规模、头哨兵、尾哨兵
	ListNode * header; 
	ListNode * trailer; 
} List;

// 初始化列表
List * initList();
// 创建新的列表节点
void newListNode(ListNode * newNode , ElemType data , ListNode * pre , ListNode * succ , List * list);
// 在列表的头哨兵节点前插入新的节点
void insertBefore(ElemType data , List * list);
// 在列表的尾哨兵节点前插入新的节点
void inserLast(ElemType data , List * list);
// 获取第一个节点
ListNode * getFirst(List * list);
// 获取最后一个节点
ListNode * getLast(List * list);
// 查找整个列表中查找
ListNode * findList(ElemType data , List * list);
// 从node节点往后 查找n个长度
ListNode * findAfterListNode(ElemType data , ListNode * node , int n);
// 从node节点往前 查找n个长度
ListNode * findBeforeListNode(ElemType data ,int n , ListNode * node);
// 删除节点
void deleteListNode(ListNode * node);
// 打印节点
void printList(List * list);
// 清除列表
void clearList(List * list);
// 去重
void deduplicate(List * list);
// 有序去重
void uniquifyBySort(List * list);
// 从头结点开始 n 长度的区间选择最大元素
ListNode * selectMax(List * list , int n);
// 交换
void list_swap(ListNode * p1 , ListNode * p2);
// 选择排序
void selectionSort(List * list);

// 插入排序 默认序列分两段 前一段为有序段，后一段为无序段，每一次从无序段中插入到有序段中合适的位置，直到结束
// 默认取第一个元素 作为有序段 依次遍历后面的元素 插入前面的有序段中
void insertionSort(List * list);
// 在节点前插入
void insertBeforeNode(ElemType data , ListNode * node);
// 在节点后插入
void insertAfterNode(ElemType data , ListNode * node);
// 选择之前序列中不大于data的最后一个节点 长度为n
ListNode * searchForInsertNode(ElemType data , int n , ListNode * node);
#endif