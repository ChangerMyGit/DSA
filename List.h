//列表节点模板类（以双向链表形式实现）
typedef struct _listNode{
	int data;
	struct _listNode * pre; // 前驱 
	struct _listNode * succ; // 后继
} ListNode;

typedef struct _list {
	int size;
	//规模、头哨兵、尾哨兵
	ListNode * header; 
	ListNode * trailer; 
} List;
// 初始化列表
void initList(List * list);
// 创建新的列表节点
void newListNode(ListNode * newNode , int data , ListNode * pre , ListNode * succ);
// 在列表的头哨兵节点前插入新的节点
void insertBefore(int data , List * list);
// 在列表的尾哨兵节点前插入新的节点
void inserLast(int data , List * list);
