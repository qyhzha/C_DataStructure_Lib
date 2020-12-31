#ifndef __LISTGRAPH_H__
#define __LISTGRAPH_H__

#include "Macro.h"
#include "LinkList.h"
#include "LinkListVertex.h"
#include "LinkListEdge.h"

STRUCT(ListGraph)
{
	LinkListVertex *list;
	int m_vCount;
	int m_eCount;
};

ListGraph* ListGraphCreate(void);
ListGraph* ListGraphDestroy(ListGraph *graph);
Bool ListGraphSetVertex(ListGraph *graph, int i, Vertex vertex);
Bool ListGraphGetVertex(ListGraph *graph, int i, Vertex *vertex);
Bool ListGraphHasVertex(ListGraph *graph, int i);
Bool ListGraphAddVertex(ListGraph *graph, Vertex vertex);
Bool ListGraphRemoveVertex(ListGraph *graph, int i, Vertex *vertex);
LinkList* ListGraphGetAdjacent(ListGraph *graph, int i);
Bool ListGraphSetEdge(ListGraph *graph, int i, int j, Edge edge);
Bool ListGraphGetEdge(ListGraph *graph, int i, int j, Edge *edge);
Bool ListGraphHasEdge(ListGraph *graph, int i, int j);
Bool ListGraphAddEdge(ListGraph *graph, int i, int j, Edge edge);
Bool ListGraphRemoveEdge(ListGraph *graph, int i, int j, Edge *edge);
int ListGraphVertexCount(ListGraph *graph);
int ListGraphEdgeCount(ListGraph *graph);
int ListGraphOutDegree(ListGraph *graph, int i);
int ListGraphInDegree(ListGraph *graph, int i);
int ListGraphIODegree(ListGraph *graph, int i);

#endif