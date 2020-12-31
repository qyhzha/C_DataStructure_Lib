#include "ListGraph.h"

ListGraph* ListGraphCreate(void)
{
	ListGraph *ret = MALLOC(ListGraph, 1);
	
	if(ret != NULL)
	{
		ret->list = LinkListVertexCreate();
		
		if(ret->list == NULL)
		{
			FREE(ret);
		}
		else
		{
			ret->m_vCount = 0;
			ret->m_eCount = 0;
		}
	}
	
	return ret;
}

ListGraph* ListGraphDestroy(ListGraph *graph)
{
	if(graph != NULL)
	{
		graph->list = LinkListVertexDestroy(graph->list);
		
		FREE(graph);
	}
	
	return NULL;
}

Bool ListGraphSetVertex(ListGraph *graph, int i, Vertex vertex)
{
	return ListGraphHasVertex(graph, i) ? (LinkListVertexMove(graph->list, i)->data->vertex = vertex, true) : false;	
}

Bool ListGraphGetVertex(ListGraph *graph, int i, Vertex *vertex)
{
	return (ListGraphHasVertex(graph, i) && (vertex != NULL)) ? (*vertex = LinkListVertexMove(graph->list, i)->data->vertex, true) : false;
}

Bool ListGraphHasVertex(ListGraph *graph, int i)
{
	return (graph != NULL) && (0 <= i) && (i < ListGraphVertexCount(graph));
}

Bool ListGraphAddVertex(ListGraph *graph, Vertex vertex)
{
	Bool ret = (graph != NULL);
	
	if(ret)
	{
		VertexNode *node = VertexNodeCreate();
		
		if(node != NULL) 
		{
			node->vertex = vertex;
			ret = LinkListVertexInsert(graph->list, LinkListVertexLength(graph->list), node);
			if(ret) graph->m_vCount++;
		}
	}
	
	return ret;
}

Bool ListGraphRemoveVertex(ListGraph *graph, int i, Vertex *vertex)
{
	Bool ret = ListGraphHasVertex(graph, i);
	
	if(ret)
	{
		VertexNode *node;
		LinkList *list = NULL;
		int j;
		
		for(j = 0; j < ListGraphVertexCount(graph); j++)
		{
			ListGraphRemoveEdge(graph, j, i, NULL);
		}
		
		ret = LinkListVertexDelete(graph->list, i, &node);
		
		for(j = 0; j < ListGraphVertexCount(graph); j++)
		{
			VertexNode *node = NULL;
			
			if(LinkListVertexGet(graph->list, j, &node))
			{
				for(LinkListEdgeMove(node->list, 0); !LinkListEdgeEnd(node->list); LinkListEdgeNext(node->list))
				{
					if(LinkListEdgeCurrent(node->list).end > i)
					{
						LinkListEdgeCurrentPtr(node->list)->end--;
					}
				}
			}			
		}
		 
		if(ret) 
		{
			if(vertex != NULL) *vertex = node->vertex;
			
			graph->m_vCount--;
		}
	}
	
	return ret;
}

LinkList* ListGraphGetAdjacent(ListGraph *graph, int i)
{
	LinkList *ret = NULL;
	
	if(ListGraphHasVertex(graph, i))
	{
		ret = LinkListCreate();
		
		if(ret != NULL)
		{
			VertexNode *node = NULL;
			
			if(LinkListVertexGet(graph->list, i, &node))
			{
				for(LinkListEdgeMove(node->list, 0); !LinkListEdgeEnd(node->list); LinkListEdgeNext(node->list))
				{
					LinkListInsert(ret, LinkListLength(ret), LinkListEdgeCurrent(node->list).end);
				}
			}
			else
			{
				ret = LinkListDestroy(ret);
			}
		}
	}
	
	return ret;
}

Bool ListGraphSetEdge(ListGraph *graph, int i, int j, Edge edge)
{
	Bool ret = ListGraphHasEdge(graph, i, j);
	
	if(ret)
	{
		VertexNode *node;
		
		ret = LinkListVertexGet(graph->list, i, &node);
		
		if(ret)
		{
			ret = false;
			
			for(LinkListEdgeMove(node->list, 0); !LinkListEdgeEnd(node->list) && !ret; LinkListEdgeNext(node->list))
			{
				if(LinkListEdgeCurrent(node->list).end == j)
				{
					LinkListEdgeCurrentPtr(node->list)->edge = edge;
					ret = true;
				}
			}
		}
	}
	
	return ret;
}

Bool ListGraphGetEdge(ListGraph *graph, int i, int j, Edge *edge)
{
	Bool ret = ListGraphHasEdge(graph, i, j) && (edge != NULL);
	
	if(ret)
	{
		VertexNode *node = NULL;
		EdgeNode en;

		ret = LinkListVertexGet(graph->list, i, &node) && LinkListEdgeGet(node->list, LinkListEdgeFind(node->list, j), &en);	
		
		*edge = en.edge;
	}
	
	return ret;
}

Bool ListGraphHasEdge(ListGraph *graph, int i, int j)
{
	Bool ret = (graph != NULL) && (0 <= i) && (i < ListGraphVertexCount(graph));
	
	if(ret)
	{
		VertexNode *node = NULL;

		ret = LinkListVertexGet(graph->list, i, &node) && ((LinkListEdgeFind(node->list, j) >= 0) ? true : false);		
	}
	
	return ret;
}

Bool ListGraphAddEdge(ListGraph *graph, int i, int j, Edge edge)
{
	Bool ret = ListGraphHasVertex(graph, i) && ListGraphHasVertex(graph, j);
	
	if(ret)
	{
		VertexNode *vertex;
		
		ret = LinkListVertexGet(graph->list, i, &vertex);
		
		if(ret)
		{
			EdgeNode node;
			
			node.end = j;
			node.edge = edge;
			
			ret = LinkListEdgeInsert(vertex->list, LinkListEdgeLength(vertex->list), node);
			
			if(ret) graph->m_eCount++;
		}
	}
	
	return ret;	
}

Bool ListGraphRemoveEdge(ListGraph *graph, int i, int j, Edge *edge)
{
	Bool ret = ListGraphHasEdge(graph, i, j);
	
	if(ret)
	{
		VertexNode *vertex;
		
		ret = LinkListVertexGet(graph->list, i, &vertex);
		
		if(ret && (vertex != NULL))
		{
			EdgeNode node;
			
			ret = LinkListEdgeDelete(vertex->list, LinkListEdgeFind(vertex->list, j), &node);
			
			if(ret) 
			{
				if(edge != NULL) *edge = node.edge;
				
				graph->m_eCount--;
			}
		}
	}
	
	return ret;	
}

int ListGraphVertexCount(ListGraph *graph)
{
	return (graph != NULL) ? graph->m_vCount : -1;
}

int ListGraphEdgeCount(ListGraph *graph)
{
	return (graph != NULL) ? graph->m_eCount : -1;
}

int ListGraphOutDegree(ListGraph *graph, int i)
{
	return (graph != NULL) ? LinkListEdgeLength(LinkListVertexMove(graph->list, i)->data->list) : -1;
}

int ListGraphInDegree(ListGraph *graph, int i)
{
	int ret = -1;
	
	if(ListGraphHasVertex(graph, i))
	{
		int j;
		
		ret = 0;
		
		for(j = 0; j < ListGraphVertexCount(graph); j++)
		{
			if(ListGraphHasEdge(graph, j, i))
			{
				ret++;
			}
		}
	}
	
	return -1;
}
int ListGraphIODegree(ListGraph *graph, int i)
{
	return ListGraphOutDegree(graph, i) + ListGraphInDegree(graph, i);
}