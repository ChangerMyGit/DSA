#include "Graph.h"
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Vector * vec;
	Edge * edge , * edge1;
	Graph * graph = initGraph();
	insertVertex(graph,'A');
	insertVertex(graph,'B');
	insertVertex(graph,'C');
	insertVertex(graph,'D');
	insertEdge(graph,"Data",100,1,2);
	insertEdge(graph,"Yes",200,3,3);
	edge = getEdge(graph,1,2);
	printf(" %c \n", ((Vertex *)getElem(graph->vertexs,0))->data);
	printf(" %c \n", ((Vertex *)getElem(graph->vertexs,1))->data);
	if(edge)
		printf(" %s %d \n", edge->data ,edge->weight);
	deleteVertex(graph,1);
	//deleteEdge(graph,1,2);
	edge1 = getEdge(graph,2,3);
	if(edge1)
		printf(" %s %d \n", edge1->data ,edge1->weight);
	return 0;
}