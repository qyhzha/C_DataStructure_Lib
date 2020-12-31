#include "MatrixGraph.h"

static Bool MatrixGraphBFSLoop(MatrixGraph *graph, int i, LinkList *vertexArray, StaticQueue *queue, Bool *flagArray)
{
	Bool ret = true;
	
	if((graph != NULL) && (vertexArray != NULL) && (queue != NULL) && (flagArray != NULL))
	{
		if(flagArray[i] == false)
		{
			flagArray[i] = true;
			StaticQueueEnqueue(queue, i);
				
			while(StaticQueueLength(queue) > 0)
			{	
				StaticQueueDequeue(queue, &i);
				LinkListInsert(vertexArray, LinkListLength(vertexArray), i);
					
				LinkList *list = MatrixGraphGetAdjacent(graph, i);
						
				if(list != NULL)
				{
					for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
					{				
						i = LinkListCurrent(list);
						
						if(flagArray[i] == false)
						{
							flagArray[i] = true;
							StaticQueueEnqueue(queue, i);
						}
					}
				}
						
				list = LinkListDestroy(list);
			}			
		}
	}
	else
	{
		ret = false;
	}
	
	return ret;
}

static Bool MatrixGraphDFSLoop(MatrixGraph *graph, int i, LinkList *vertexArray, Bool *flagArray)
{
	Bool ret = true;
	
	if((graph != NULL) && (vertexArray != NULL) && (flagArray != NULL))
	{
		if(flagArray[i] == false)
		{
			flagArray[i] = true;
			LinkListInsert(vertexArray, LinkListLength(vertexArray), i);
					
			LinkList *list = MatrixGraphGetAdjacent(graph, i);
						
			if(list != NULL)
			{
				for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
				{				
					ret = MatrixGraphDFSLoop(graph, LinkListCurrent(list), vertexArray, flagArray);
				}
						
				list = LinkListDestroy(list);
			}
		}
	}
	else
	{
		ret = false;
	}
	
	return ret;
}

MatrixGraph* MatrixGraphCreate(void)
{
	MatrixGraph *ret = MALLOC(MatrixGraph, 1);
	
	if(ret != NULL)
	{
		int i, j;
		
		for(i = 0; i < __MATRIXGRAPH_SIZE; i++)
		{
			ret->vertexes[i] = NULL;
			
			for(j = 0; j < __MATRIXGRAPH_SIZE; j++)
			{
				ret->edges[i][j] = NULL;
			}
		}
		
		ret->m_vCount = 0;
		ret->m_eCount = 0;
	}
	
	return ret;
}

MatrixGraph* MatrixGraphDestroy(MatrixGraph *graph)
{
	if(graph != NULL)
	{
		int i, j;
		
		for(i = 0; i < __MATRIXGRAPH_SIZE; i++)
		{
			FREE(graph->vertexes[i]);
			
			for(j = 0; j < __MATRIXGRAPH_SIZE; j++)
			{
				FREE(graph->edges[i][j]);
			}
		}
		
		FREE(graph);
	}
	
	return NULL;
}

Bool MatrixGraphSetVertex(MatrixGraph *graph, int i, Vertex vertex)
{
	Bool ret = (graph != NULL) && (0 <= i) && (i < MatrixGraphCapacity(graph));
	
	if(ret)
	{
		if(graph->vertexes[i] == NULL) 
		{
			graph->vertexes[i] = MALLOC(Vertex, 1);
			
			if(graph->vertexes[i] != NULL)
			{
				graph->m_vCount++;
			}
		}
		
		if(graph->vertexes[i] != NULL)
		{
			*(graph->vertexes[i]) = vertex;
		}
		else
		{
			ret = false;
		}
	}
	
	return ret;
}

Bool MatrixGraphGetVertex(MatrixGraph *graph, int i, Vertex *vertex)
{
	return MatrixGraphHasVertex(graph, i) && (vertex != NULL)\
	? (*vertex = *(graph->vertexes[i]), true) : false;	
}

Bool MatrixGraphGetVertexPtr(MatrixGraph *graph, int i, Vertex **vertex)
{
	return MatrixGraphHasVertex(graph, i) && (vertex != NULL)\
	? (*vertex = graph->vertexes[i], true) : false;		
}

Bool MatrixGraphHasVertex(MatrixGraph *graph, int i)
{
	return ((graph != NULL) && (0 <= i) && (i < MatrixGraphCapacity(graph)) && (graph->vertexes[i] != NULL));	
}

Bool MatrixGraphRemoveVertex(MatrixGraph *graph, int i, Vertex *vertex)
{
	Bool ret = MatrixGraphHasVertex(graph, i);
	
	if(ret)
	{
		if(vertex != NULL) *vertex = *(graph->vertexes[i]);
			
		FREE(graph->vertexes[i]);
			
		graph->m_vCount--;
	}
	
	return ret;		
}

int MatrixGraphFindVertex(MatrixGraph *graph, Vertex *vertex)
{
	int ret = -1;
	
	if((graph != NULL) && (vertex != NULL))
	{
		int i;
		
		for(i = 0; i < __MATRIXGRAPH_SIZE; i++)
		{
			if(graph->vertexes[i] == vertex)
			{
				ret = i;
				break;
			}
		}
	}
	
	return ret;
}

LinkList* MatrixGraphGetAdjacent(MatrixGraph *graph, int i)
{
	LinkList *ret = NULL;
	
	if(MatrixGraphHasVertex(graph, i))
	{
		ret = LinkListCreate();
		
		if(ret != NULL)
		{
			int j;
			
			for(j = 0; j < MatrixGraphCapacity(graph); j++)
			{
				if(graph->edges[i][j] != NULL)
				{
					LinkListInsert(ret, LinkListLength(ret), j);
				}
			}
		}
	}
	
	return ret;
}

Bool MatrixGraphSetEdge(MatrixGraph *graph, int i, int j, Edge edge)
{
	Bool ret = MatrixGraphHasVertex(graph, i) && MatrixGraphHasVertex(graph, j);
	
	if(ret)
	{
		if(graph->edges[i][j] == NULL) 
		{
			graph->edges[i][j] = MALLOC(Edge, 1);
			
			if(graph->edges[i][j] != NULL)
			{
				graph->m_eCount++;
			}
		}
		
		if(graph->edges[i][j] != NULL)
		{
			*(graph->edges[i][j]) = edge;
		}
		else
		{
			ret = false;
		}
	}
	
	return ret;	
}

Bool MatrixGraphGetEdge(MatrixGraph *graph, int i, int j, Edge *edge)
{
	return MatrixGraphHasEdge(graph, i, j) && (edge != NULL)\
	? (*edge = *(graph->edges[i][j]), true) : false;		
}

Bool MatrixGraphHasEdge(MatrixGraph *graph, int i, int j)
{
	return ((graph != NULL) && (0 <= i) && (i < MatrixGraphCapacity(graph)) && \
	(0 <= j) && (j < MatrixGraphCapacity(graph)) && (graph->edges[i][j] != NULL));	
}

Bool MatrixGraphRemoveEdge(MatrixGraph *graph, int i, int j, Edge *edge)
{
	Bool ret = MatrixGraphHasEdge(graph, i, j);
	
	if(ret)
	{
		if(edge != NULL) *edge = *(graph->edges[i][j]);
			
		FREE(graph->edges[i][j]);
			
		graph->m_eCount--;
	}
	
	return ret;		
}

int MatrixGraphCapacity(MatrixGraph *graph)
{
	return (graph != NULL) ? __MATRIXGRAPH_SIZE : -1;
}

int MatrixGraphVertexCount(MatrixGraph *graph)
{
	return (graph != NULL) ? graph->m_vCount : -1;
}
int MatrixGraphEdgeCount(MatrixGraph *graph)
{
	return (graph != NULL) ? graph->m_eCount : -1;
}

int MatrixGraphOutDegree(MatrixGraph *graph, int i)
{
	int ret = -1;
	
	if(MatrixGraphHasVertex(graph, i))
	{
		int j;
		
		ret = 0;
		
		for(j = 0; j < MatrixGraphCapacity(graph); j++)
		{
			if(graph->edges[i][j] != NULL)
			{
				ret++;
			}
		}
	}
	
	return ret;
}

int MatrixGraphInDegree(MatrixGraph *graph, int i)
{
	int ret = -1;
	
	if(MatrixGraphHasVertex(graph, i))
	{
		int j;
		
		ret = 0;
		
		for(j = 0; j < MatrixGraphCapacity(graph); j++)
		{
			if(graph->edges[j][i] != NULL)
			{
				ret++;
			}
		}
	}
	
	return ret;
}

int MatrixGraphIODegree(MatrixGraph *graph, int i)
{
	return MatrixGraphOutDegree(graph, i) + MatrixGraphInDegree(graph, i);
}

LinkList* MatrixGraphBFS(MatrixGraph *graph, int i)
{
	LinkList *ret = NULL;
	
	if((graph != NULL) && (MatrixGraphHasVertex(graph, i)))
	{
		ret = LinkListCreate();
		
		if(ret != NULL)
		{
			StaticQueue *queue = StaticQueueCreate();
			Bool *flagArray = MALLOC(Bool, __MATRIXGRAPH_SIZE);
			
			memset(flagArray, 0, __MATRIXGRAPH_SIZE * sizeof(Bool));
			
			Bool ok = MatrixGraphBFSLoop(graph, i, ret, queue, flagArray);
			
			if(ok == false)
			{
				ret = LinkListDestroy(ret);
			}
			
			flagArray = FREE(flagArray);
			queue = StaticQueueDestroy(queue);
		}
	}
	
	return ret;
}

LinkList* MatrixGraphDFS(MatrixGraph *graph, int i)
{
	LinkList *ret = NULL;
	
	if((graph != NULL) && (MatrixGraphHasVertex(graph, i)))
	{
		ret = LinkListCreate();
		
		if(ret != NULL)
		{
			Bool *flagArray = MALLOC(Bool, __MATRIXGRAPH_SIZE);
			
			memset(flagArray, 0, __MATRIXGRAPH_SIZE * sizeof(Bool));
			
			Bool ok = MatrixGraphDFSLoop(graph, i, ret, flagArray);
			
			if(ok == false)
			{
				ret = LinkListDestroy(ret);
			}
			
			flagArray = FREE(flagArray);
		}
	}
	
	return ret;
}