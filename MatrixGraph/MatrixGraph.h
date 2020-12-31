#ifndef __MATRIXGRAPH_H__
#define __MATRIXGRAPH_H__

#include "Macro.h"
#include "LinkList.h"
#include "StaticQueue.h"

STRUCT(MatrixGraph)
{
	Vertex *vertexes[__MATRIXGRAPH_SIZE];
	Edge *edges[__MATRIXGRAPH_SIZE][__MATRIXGRAPH_SIZE];
	int m_vCount;
	int m_eCount;
};

MatrixGraph* MatrixGraphCreate(void);
MatrixGraph* MatrixGraphDestroy(MatrixGraph *graph);
Bool MatrixGraphSetVertex(MatrixGraph *graph, int i, Vertex vertex);
Bool MatrixGraphGetVertex(MatrixGraph *graph, int i, Vertex *vertex);
Bool MatrixGraphGetVertexPtr(MatrixGraph *graph, int i, Vertex **vertex);
Bool MatrixGraphHasVertex(MatrixGraph *graph, int i);
Bool MatrixGraphRemoveVertex(MatrixGraph *graph, int i, Vertex *vertex);
int MatrixGraphFindVertex(MatrixGraph *graph, Vertex *vertex);
LinkList* MatrixGraphGetAdjacent(MatrixGraph *graph, int i);
Bool MatrixGraphSetEdge(MatrixGraph *graph, int i, int j, Edge edge);
Bool MatrixGraphGetEdge(MatrixGraph *graph, int i, int j, Edge *edge);
Bool MatrixGraphHasEdge(MatrixGraph *graph, int i, int j);
Bool MatrixGraphRemoveEdge(MatrixGraph *graph, int i, int j, Edge *edge);
int MatrixGraphCapacity(MatrixGraph *graph);
int MatrixGraphVertexCount(MatrixGraph *graph);
int MatrixGraphEdgeCount(MatrixGraph *graph);
int MatrixGraphOutDegree(MatrixGraph *graph, int i);
int MatrixGraphInDegree(MatrixGraph *graph, int i);
int MatrixGraphIODegree(MatrixGraph *graph, int i);
LinkList* MatrixGraphDFS(MatrixGraph *graph, int i);

#endif