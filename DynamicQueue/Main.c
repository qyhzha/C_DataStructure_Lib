#include "DynamicQueue.h"
#include <stdio.h>

int main()
{
	DynamicQueue* queue = DynamicQueueCreate();
	
	if(queue != NULL)
	{
		int i, len = -1, data = -1;
		
		for(i = 0; i < 100; i++)
		{
			DynamicQueueEnqueue(queue, i);
		}
		
		len = DynamicQueueLength(queue);
		printf("len = %d\n\n", len);
		
		for(i = 0; i < len / 2; i++)
		{
			DynamicQueueDequeue(queue, NULL);
		}
		
		len = DynamicQueueLength(queue);
		printf("len = %d\n\n", len);
		
		printf("打印队列中元素：\n");
		for(i = 0; i < len; i++)
		{
			int data;
			DynamicQueueDequeue(queue, &data);
			printf("queue[%02d] = %-2d\n", i, data);
		}
		
		printf("\n删除状态：%d\n\n", DynamicQueueDequeue(queue, NULL));
		printf("获取数据元素状态：%d\n\n", DynamicQueueFront(queue, &data));
	
		queue = DynamicQueueDestroy(queue);
		len = DynamicQueueLength(queue);
		printf("len = %d\n\n", len);
	}
	
	return 0;
}