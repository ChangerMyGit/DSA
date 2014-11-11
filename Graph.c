#include "Graph.h"
#include "Vector.h"
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
	Vertex * vertex = newVertex(data); // �½ڵ� 
	Vector * vertexs;
	Vector * edges ;
	insert(graph->vertexs , vertex);
	graph->n++;//��������1
	// ���Ȱ�֮ǰ�ľ�������
	for(i = 0 ; i < graph->edges->size ; i++){
		vertexs = graph->edges->elem[0];
		insert(vertexs , vertex);
	}
	// ����µı�
	edges = initVector(graph->n * sizeof(Edge)); // �µı�
	insert(graph->edges , edges);
	graph->e++;
}