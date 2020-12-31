#include "MatrixGraph.h"
#include <stdio.h>

int main()
{
	MatrixGraph *graph = MatrixGraphCreate();
	
	if(graph != NULL)
	{
		int i;
		
		printf("��ʼ��ͼ��\n");
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
			printf("��ʼ��ӡ5���ڱߣ�\n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("%d��5���ڱߡ�\n", LinkListCurrent(list));
			}
			
			list = LinkListDestroy(list);
		}
		
		printf("��ӡ4����ȣ�%d\n", MatrixGraphInDegree(graph, 4));
		
		printf("��ӡ��������%d\n", MatrixGraphVertexCount(graph));
		
		printf("����ͼ��\n");
		list = MatrixGraphDFS(graph, 1);
		if(list != NULL)
		{
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("�ڵ㣺%d\n", LinkListCurrent(list));
			}
			
			list = LinkListDestroy(list);
		}
		
		graph = MatrixGraphDestroy(graph);
	}
	
	return 0;
}