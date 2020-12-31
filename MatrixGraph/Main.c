#include "MatrixGraph.h"
#include <stdio.h>

int main()
{
	MatrixGraph *graph = MatrixGraphCreate();
	
	if(graph != NULL)
	{
		int i;
		
		printf("开始画图：\n");
		for(i = 0; i < MatrixGraphCapacity(graph); i++)
		{
			printf("flag = %d\n", MatrixGraphSetVertex(graph, i, 0));			
		}

		printf("flag = %d\n", MatrixGraphSetEdge(graph, 1, 2, 0));
		printf("flag = %d\n", MatrixGraphSetEdge(graph, 1, 3, 0));
		printf("flag = %d\n", MatrixGraphSetEdge(graph, 2, 7, 0));
		printf("flag = %d\n", MatrixGraphSetEdge(graph, 3, 6, 0));
		printf("flag = %d\n", MatrixGraphSetEdge(graph, 3, 4, 0));
		printf("flag = %d\n", MatrixGraphSetEdge(graph, 4, 1, 0));
		printf("flag = %d\n", MatrixGraphSetEdge(graph, 5, 2, 0));
		printf("flag = %d\n", MatrixGraphSetEdge(graph, 5, 4, 0));
		printf("flag = %d\n", MatrixGraphSetEdge(graph, 6, 8, 0));
		printf("flag = %d\n", MatrixGraphSetEdge(graph, 7, 4, 0));
		printf("flag = %d\n", MatrixGraphSetEdge(graph, 9, 4, 0));
		
		LinkList *list = MatrixGraphGetAdjacent(graph, 5);
		
		if(list != NULL)
		{
			printf("开始打印5的邻边：\n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("%d是5的邻边。\n", LinkListCurrent(list));
			}
			
			list = LinkListDestroy(list);
		}
		
		printf("打印4的入度：%d\n", MatrixGraphInDegree(graph, 4));
		
		printf("打印顶点数：%d\n", MatrixGraphVertexCount(graph));
		
		printf("遍历图：\n");
		list = MatrixGraphDFS(graph, 1);
		if(list != NULL)
		{
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("节点：%d\n", LinkListCurrent(list));
			}
			
			list = LinkListDestroy(list);
		}
		
		graph = MatrixGraphDestroy(graph);
	}
	
	return 0;
}