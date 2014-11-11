#include "Vector.h"
/**
ʹ���ڽӾ����ʾͼ
**/

// ����״̬
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; 
// ���ڱ�����������������
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; 

// Vertex ͼ�Ķ���
typedef struct _vertex {
	// ����
	Elem data;
	// ���������״̬
	int inDegree, outDegree; VStatus status; 
	int parent; int priority; //�ڱ������еĸ��ڵ㡢���ȼ���
} Vertex;

typedef struct _edge {
	//���ݡ�Ȩ�ء�����
	Elem data; 
	int weight; 
	EType type; 
} Edge;

// ͼ
typedef struct _graph{
	Vector * vertexs;// ���㼯
	Vector * edges;// �߼�
	int n , e ; // ������ �ߵ�����
} Graph;

// ��ʼ��ͼ
Graph * initGraph();
// �����µĶ���
Vertex * newVertex(Elem data);
// �����µı�
Edge * newEdge(Elem data , int w);
// �������
void insertVertex(Graph * graph , Elem data);