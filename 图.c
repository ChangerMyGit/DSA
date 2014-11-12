#include "Graph.h"
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Vector * vec;
	Edge * edge , * edge1;
	// 构建图 节点和 边
	Graph * graph = initGraph();
	insertVertex(graph,'A');
	insertVertex(graph,'B');
	insertVertex(graph,'C');
	insertVertex(graph,'D');
	insertVertex(graph,'E');
	insertVertex(graph,'F');
	insertVertex(graph,'G');
	insertVertex(graph,'S');
	insertEdge(graph,"AE",1,0,4);
	insertEdge(graph,"AS",1,0,7);
	insertEdge(graph,"BC",1,1,2);
	insertEdge(graph,"BD",1,1,3);
	insertEdge(graph,"CA",1,2,0);
	insertEdge(graph,"CB",1,2,1);
	insertEdge(graph,"CS",1,2,7);
	insertEdge(graph,"DB",1,3,1);
	insertEdge(graph,"DS",1,3,7);
	insertEdge(graph,"EA",1,4,0);
	insertEdge(graph,"EF",1,4,5);
	insertEdge(graph,"EG",1,4,6);
	insertEdge(graph,"FE",1,5,4);
	insertEdge(graph,"FG",1,5,6);
	insertEdge(graph,"GE",1,6,4);
	insertEdge(graph,"GF",1,6,5);
	insertEdge(graph,"GB",1,6,1);
	insertEdge(graph,"SA",1,7,0);
	insertEdge(graph,"SC",1,7,2);
	insertEdge(graph,"SD",1,7,3);
/**
	edge = getEdge(graph,1,2);
	printf(" %c \n", ((Vertex *)getElem(graph->vertexs,0))->data);
	printf(" %c \n", ((Vertex *)getElem(graph->vertexs,1))->data);
	printGraph(graph);
	deleteVertex(graph,1);
	insertEdge(graph,"OK",300,2,1);
**/
/**
	if(edge)
		printf(" %s %d \n", edge->data ,edge->weight);
	deleteVertex(graph,1);
	//deleteEdge(graph,1,2);
	edge1 = getEdge(graph,2,3);
	if(edge1)
		printf(" %s %d \n", edge1->data ,edge1->weight);
	printf("\n");
**/
	BFS(graph,7);
	printGraph(graph);
	return 0;
}