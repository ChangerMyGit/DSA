//�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
typedef struct _listNode{
	int data;
	struct _listNode * pre; // ǰ�� 
	struct _listNode * succ; // ���
} ListNode;

typedef struct _list {
	int size;
	//��ģ��ͷ�ڱ���β�ڱ�
	ListNode * header; 
	ListNode * trailer; 
} List;
// ��ʼ���б�
void initList(List * list);
// �����µ��б�ڵ�
void newListNode(ListNode * newNode , int data , ListNode * pre , ListNode * succ);
// ���б��ͷ�ڱ��ڵ�ǰ�����µĽڵ�
void insertBefore(int data , List * list);
// ���б��β�ڱ��ڵ�ǰ�����µĽڵ�
void inserLast(int data , List * list);
