#include "Graph.h"
#include "Vector.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

Graph * initGraph(){
	int i;
	Graph * graph = (Graph *)malloc(sizeof(Graph));
	graph->vertexs = initVector(10 * sizeof(Vertex));
	graph->edges = initVector(10 * sizeof(Vector));
	/*
	for(i = 0 ; i < graph->edges->size ; i++)
	graph->edges->elem[i] = initVector(10 * sizeof(Edge));
	*/	
	graph->n = 0;
	graph->e = 0;
	return graph;
}

Vertex * newVertex(Elem data){
	Vertex * vertex = (Vertex *)malloc(sizeof(Vertex));
	vertex->data = data;
	vertex->inDegree = 0;
	vertex->outDegree = 0;
	vertex->parent = -1;
	vertex->priority = -1;
	vertex->status = UNDISCOVERED;
	return vertex;
}

Edge * newEdge(Elem data , int w){
	Edge * edge = (Edge *)malloc(sizeof(Edge));
	edge->data = data;
	edge->weight = w;
	edge->type = UNDETERMINED;
	return edge;
}

void insertVertex(Graph * graph , Elem data){
	int i;
	Vertex * vertex = newVertex(data); // 新节点 
	Vector * vertexs;
	Vector * edges ;
	insert(graph->vertexs , vertex);
	graph->n++;//顶点数加1
	// 首先把之前的矩阵扩充
	for(i = 0 ; i < graph->edges->size ; i++){
		vertexs = graph->edges->elem[i];
		insert(vertexs , NULL);
	}
	// 添加新的边
	edges = initVector(graph->n * sizeof(Edge)); // 新的边
	for(i = 0 ; i < graph->n ; i++)
		insert(edges , NULL); // edges->elem[i] = NULL;
	insert(graph->edges , edges);
}

void deleteVertex(Graph * graph , int i){
	int j , k;
	Vector * vertexs;
	Vector * edges ;
	if(graph->n == 0 || i > graph->n) return ;
	// 删除单个顶点
	deleteSingle(graph->vertexs,i);
	edges = graph->edges;
	for(j = 0;j < graph->n;j++){
		vertexs = graph->edges->elem[j];
		for(k = 0; k< graph->n ;k++){
			if(existEdge(graph,i,k))
				deleteEdge(graph,i,k); // 如果要删除的边之前存在 删除
		}
		deleteSingle(vertexs,i);
	}
	for(j = 0;j < graph->n;j++){
		vertexs = graph->edges->elem[j];
		// 然后删除纵向的元素
		//deleteSingle(vertexs,i);
	}
	// 符合条件的边都删除之后，删除横向元素
	deleteSingle(graph->edges,i);
	graph->n--;
}

int existEdge(Graph * graph , int i, int j){
	Vector * edges;
	Edge * edge;
	if(graph->e == 0 ) return FALSE;
	// 边的集合
	edges = getElem(graph->edges , i);
	edge = getElem(edges,j);
	return (edge == NULL) ? FALSE : TRUE;
}

Edge * getEdge(Graph * graph , int i , int j){
	Edge * edge;
	Vector * edges;
	if(existEdge(graph,i,j)){
		edges = getElem(graph->edges , i);
		edge = edges->elem[j];
		return edge;
	}
	return NULL;
}

void insertEdge(Graph * graph , Elem data , int w , int i, int j){
	Edge * edge;
	Vector * edges;
	if(existEdge(graph , i , j)) return ; // 如果边存在忽略
	edge = newEdge(data ,w);
	edges = getElem(graph->edges , i);
	edges->elem[j] = edge;
	graph->e++;
}

void deleteEdge(Graph * graph , int i , int j){
	Edge * edge;
	Vector * edges;
	if(!existEdge(graph , i , j)) return;
	edges = getElem(graph->edges , i);
	edge = getElem(edges , j);
	free(edge);
	edges->elem[j] = NULL;// 重新指向
	graph->e--;
}

void printGraph(Graph * graph){
	int i , j;
	Edge * edge;
	Vector * edgs;
	Vector * edgess = graph->edges;
	for(i = 0;i < graph->n ; i++){
		edgs = getElem(edgess,i);
		for(j = 0;j < graph->n ; j++){
			edge = getElem(edgs,j);
			printf("%3d  " , (edge == NULL) ? 0 : edge->weight);
		}
		printf("\n");
	}
}

int nextNbr(Graph * graph , int i, int j){
	while(j >= 0 && !existEdge(graph , i , --j))
		;// 逆序查找最近的邻接顶点
	return j;
}

int firstNbr(Graph * graph ,int i){
	return nextNbr(graph,i,graph->n);
}

// 广度优先遍历 v 顶点的次序
void BFS(Graph * graph , int v){
	int u;
	Vertex * vertex ;
	// 初始化队列
	Queue * queue = initQueue();
	vertex = graph->vertexs->elem[v];
	// 首个顶点入队
	enqueue(v,queue);
	//vertex->status = DISCOVERED;
	updateStatus(graph,v,DISCOVERED);
	while(!emptyQueue(queue)){
	   v = dequeue(queue);
	   //vertex = graph->vertexs->elem[v];
	   for(u = firstNbr(graph, v) ; u >= 0;u = nextNbr(graph,v,u)){
		   vertex = graph->vertexs->elem[u];
		   // 如果节点尚未发现
		   if(vertex->status == UNDISCOVERED){
			   updateStatus(graph,u,VISITED);
			   enqueue(u,queue);
		   }
	   }  
	   //vertex->status = VISITED;
	   updateStatus(graph,v,VISITED);
	}
}

void updateStatus(Graph * graph , int v , VStatus status){
	Vertex * vertex = getElem(graph->vertexs,v);
	vertex->status = status;
}