#include "ListGraph.h"
#include <stdio.h>

int main()
{
	ListGraph *graph = ListGraphCreate();
	
	if(graph != NULL)
	{
		LinkList *list = NULL;
		int i, j;
		
		printf("开始插入顶点：\n");
		for(i = 0; i < 10; i++)
		{
			printf("flag = %d\n", ListGraphAddVertex(graph, 0));
		}
		
		printf("开始插入边：\n");
		printf("flag = %d\n", ListGraphAddEdge(graph, 1, 2, 0));
		printf("flag = %d\n", ListGraphAddEdge(graph, 1, 3, 0));
		printf("flag = %d\n", ListGraphAddEdge(graph, 2, 7, 0));
		printf("flag = %d\n", ListGraphAddEdge(graph, 3, 4, 0));
		printf("flag = %d\n", ListGraphAddEdge(graph, 3, 6, 0));
		printf("flag = %d\n", ListGraphAddEdge(graph, 4, 1, 0));
		printf("flag = %d\n", ListGraphAddEdge(graph, 5, 2, 0));
		printf("flag = %d\n", ListGraphAddEdge(graph, 5, 4, 0));
		printf("flag = %d\n", ListGraphAddEdge(graph, 6, 8, 0));
		printf("flag = %d\n", ListGraphAddEdge(graph, 7, 4, 0));
		printf("flag = %d\n", ListGraphAddEdge(graph, 9, 4, 0));

		i = 1;
		list = ListGraphGetAdjacent(graph, i);
		
		printf("打印%d的邻边：\n", i);
		for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
		{
			printf("%d的邻边有%d\n", i, LinkListCurrent(list));
		}
		
		list = LinkListDestroy(list);
		
		printf("是否有顶点：\n");
		for(i = 0; i < 12; i++)
		{
			printf("%d是否有顶点：%d\n", i, ListGraphHasVertex(graph, i));
		}
		
		printf("\n");
	
		printf("是否有边：\n");
		for(i = 0; i < 10; i++)
		{
			for(j = 0; j < 10; j++)
			{
				printf("%-2d", ListGraphHasEdge(graph, i, j));
			}
			
			printf("\n");
		}
		
		printf("\n");
		
		printf("顶点数目：%d\n", ListGraphVertexCount(graph));
		printf("边数目：%d\n", ListGraphEdgeCount(graph));
		
		ListGraphRemoveVertex(graph, 4, NULL);
		
		printf("是否有边：\n");
		for(i = 0; i < ListGraphVertexCount(graph); i++)
		{
			for(j = 0; j < ListGraphVertexCount(graph); j++)
			{
				printf("%-2d", ListGraphHasEdge(graph, i, j));
			}
			
			printf("\n");
		}
	
		graph = ListGraphDestroy(graph);
	}
	
	return 0;
}