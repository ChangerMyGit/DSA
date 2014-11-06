// ����ͷ�ļ��ظ�����
#ifndef _LIST_H
#define _LIST_H
// ͨ������
typedef  void * ElemType;
//�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
typedef struct _listNode{
	ElemType data;// ͨ����������
	struct _listNode * pre; // ǰ�� 
	struct _listNode * succ; // ���
	struct _list * list;
} ListNode;

typedef struct _list {
	int size;
	//��ģ��ͷ�ڱ���β�ڱ�
	ListNode * header; 
	ListNode * trailer; 
} List;

// ��ʼ���б�
List * initList();
// �����µ��б�ڵ�
void newListNode(ListNode * newNode , ElemType data , ListNode * pre , ListNode * succ , List * list);
// ���б��ͷ�ڱ��ڵ�ǰ�����µĽڵ�
void insertBefore(ElemType data , List * list);
// ���б��β�ڱ��ڵ�ǰ�����µĽڵ�
void inserLast(ElemType data , List * list);
// ��ȡ��һ���ڵ�
ListNode * getFirst(List * list);
// ��ȡ���һ���ڵ�
ListNode * getLast(List * list);
// ���������б��в���
ListNode * findList(ElemType data , List * list);
// ��node�ڵ����� ����n������
ListNode * findAfterListNode(ElemType data , ListNode * node , int n);
// ��node�ڵ���ǰ ����n������
ListNode * findBeforeListNode(ElemType data ,int n , ListNode * node);
// ɾ���ڵ�
void deleteListNode(ListNode * node);
// ��ӡ�ڵ�
void printList(List * list);
// ����б�
void clearList(List * list);
// ȥ��
void deduplicate(List * list);
// ����ȥ��
void uniquifyBySort(List * list);
// ��ͷ��㿪ʼ n ���ȵ�����ѡ�����Ԫ��
ListNode * selectMax(List * list , int n);
// ����
void list_swap(ListNode * p1 , ListNode * p2);
// ѡ������
void selectionSort(List * list);

// �������� Ĭ�����з����� ǰһ��Ϊ����Σ���һ��Ϊ����Σ�ÿһ�δ�������в��뵽������к��ʵ�λ�ã�ֱ������
// Ĭ��ȡ��һ��Ԫ�� ��Ϊ����� ���α��������Ԫ�� ����ǰ����������
void insertionSort(List * list);
// �ڽڵ�ǰ����
void insertBeforeNode(ElemType data , ListNode * node);
// �ڽڵ�����
void insertAfterNode(ElemType data , ListNode * node);
// ѡ��֮ǰ�����в�����data�����һ���ڵ� ����Ϊn
ListNode * searchForInsertNode(ElemType data , int n , ListNode * node);
#endif