#include "Vector.h"
/**
使用邻接矩阵表示图
**/

// 顶点状态
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; 
// 边在遍历树中所属的类型
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; 

// Vertex 图的顶点
typedef struct _vertex {
	// 数据
	Elem data;
	// 出入度数、状态
	int inDegree, outDegree; VStatus status; 
	int parent; int priority; //在遍历树中的父节点、优先级数
	int clock;// 计数器 用于计算顶点被遍历的次序
} Vertex;

typedef struct _edge {
	//数据、权重、类型
	Elem data; 
	int weight; 
	EType type; 
} Edge;

// 图
typedef struct _graph{
	Vector * vertexs;// 顶点集
	Vector * edges;// 边集
	int n , e ; // 顶点数 边的数量
} Graph;

// 初始化图
Graph * initGraph();
// 创建新的顶点
Vertex * newVertex(Elem data);
// 创建新的边
Edge * newEdge(Elem data , int w);
// 顶点插入
void insertVertex(Graph * graph , Elem data);
// 删除顶点
void deleteVertex(Graph * graph , int i);
// 边插入
void insertEdge(Graph * graph , Elem data , int w , int i, int j);
// 边是否存在
int existEdge(Graph * graph , int i, int j);
// 获取边
Edge * getEdge(Graph * graph , int i , int j);
// 边删除
void deleteEdge(Graph * graph , int i , int j);
// 打印图
void printGraph(Graph * graph);
// 打印图的顶点
void printfVertexs(Graph * graph);
// 获取下一个邻接顶点
int nextNbr(Graph * graph , int i, int j);
// 获取首个邻接顶点
int firstNbr(Graph * graph ,int i);
// 广度优先遍历 v 顶点的次序
void BFS(Graph * graph , int v);
// 深度优先遍历 v 顶点的次序
void DFS(Graph * graph , int v);
// 更新节点状态
void updateStatus(Graph * graph , int v);
// 更新顶点时间
void dTime(Graph * graph , int v , int clock);