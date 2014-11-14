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
	vertex->clock = 0;
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

void printfVertexs(Graph * graph){
	int i ;
	Vertex * vertex;
	Vector * vertexs = graph->vertexs;
	for(i = 0;i < graph->n ; i++){
	   vertex = (Vertex *)getElem(vertexs,i);
	   printf(" %d %c %d \n" , vertex->clock , vertex->data , vertex->status);
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
	int u ,clock = 0;
	Vertex * vertex ;
	// 初始化队列
	Queue * queue = initQueue();
	vertex = graph->vertexs->elem[v];
	// 首个顶点入队
	enqueue(v,queue);
	updateStatus(graph,v,DISCOVERED);
	while(!emptyQueue(queue)){
	   v = dequeue(queue);
	   dTime(graph,v,++clock);
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

void dTime(Graph * graph , int v, int clock){
	Vertex * vertex = getElem(graph->vertexs,v);
	vertex->clock = clock;
}

/**
   不断向下递归查找还没访问到的顶点元素
   如果递归到最后一级 跳出递归到上一级 再次循环处理
   对于有向图可能存在访问不到节点的情况 所以可以使用遍历所有顶点元素
   然后，依次使用DFS遍历。
**/
void DFS(Graph * graph , int v){
    int u ,clock = 0;
	Vertex * nextVer,  * vertex = (Vertex *)getElem(graph->vertexs,v);
	updateStatus(graph,v,DISCOVERED);// 置状态为已探索
	for(u = firstNbr(graph,v); u >=0 ;u = nextNbr(graph,v,u)){
	   nextVer = (Vertex *)getElem(graph->vertexs,u);
	   // 如果未探索递归处理
	   if(nextVer->status == UNDISCOVERED){
	       DFS(graph,u);
	   }
	}
	// 全部处理完毕后之状态为已访问
	updateStatus(graph,v,VISITED);
}

void Dijkstra(Graph * graph , int v){
	int i;
	Vertex * vertex;
	Edge * edge;
	Vector * u = initVector(graph->n * sizeof(Vertex));
	int * dist = (int *)malloc(graph->n * sizeof(int));
	// 初始化U 集合
	for(i = 0 ; i < graph->n ; i++){
		if( i!= v)
			insert(u,i);
	}
	// 初始化权值为-1
	for(i = 0 ; i < graph->n ; i++){
		edge = getEdge(graph,v,i);
		//dist[i] = (edge == NULL) ? 0 : edge->weight;
		dist[i] = -1;
	}

	while(u->size > 0){
		v = getMinEdge(graph,u,v,dist);
	}
	for(i = 0 ; i < graph->n ; i++){
		printf("%3d",dist[i]);
	}
	printf("\n");
}

int getMinEdge(Graph * graph , Vector * u  , int v, int * dist){
	int i , min = -1 , weight = -1 , res , temp;
	Edge * edge = NULL;
	for(i = 0 ; i < u->size ; i++){
		temp = (int)getElem(u,i);
		edge = getEdge(graph , v ,temp);
		if(min == -1 && weight == -1 && edge!=NULL){
			min = i;
			weight = edge->weight;
			if(v == 0)
				updateQuan(dist,temp,edge->weight);
			else
				updateQuan(dist,temp,dist[v] + edge->weight);
		}
		else{
			if(edge!=NULL) {
				if(edge->weight < weight){
					min = i;
				    weight = edge->weight;
				}
				if(v == 0)
					updateQuan(dist,temp,edge->weight);
				else
					updateQuan(dist,temp,dist[v] + edge->weight);				
			}
		}
	}
	res = (int)getElem(u,min);
	deleteSingle(u,min);
	return res;
}

void updateQuan(int * dist , int i , int weight){
	int quan = dist[i];
	if(quan == -1) 
		dist[i] = weight;
	else if(quan > weight)
		dist[i] = weight;
}