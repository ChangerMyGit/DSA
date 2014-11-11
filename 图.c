#include "Graph.h"
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Vector * vec;
	Edge * edge;
	Graph * graph = initGraph();
	insertVertex(graph,'A');
	vec = getElem(graph->edges,0);
	edge = getElem(vec,0);
	printf(" %c \n", ((Vertex *)getElem(graph->vertexs,0))->data);
	return 0;
}