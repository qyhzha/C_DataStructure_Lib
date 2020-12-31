#include "StaticQueue.h"
#include <stdio.h>

int main()
{
	StaticQueue* queue = StaticQueueCreate();
	
	if(queue != NULL)
	{
		int i, len = -1, data = -1;
		
		for(i = 0; i < StaticQueueCapacity(queue); i++)
		{
			StaticQueueEnqueue(queue, i);
		}
		
		printf("插入状态：%d\n\n", StaticQueueEnqueue(queue, 100));
		
		len = StaticQueueLength(queue);
		printf("len = %d\n\n", len);
		
		for(i = 0; i < len / 2; i++)
		{
			StaticQueueDequeue(queue, NULL);
		}
		
		len = StaticQueueLength(queue);
		printf("len = %d\n\n", len);
		
		printf("打印队列中元素：\n");
		for(i = 0; i < len; i++)
		{
			int data;
			StaticQueueDequeue(queue, &data);
			printf("queue[%02d] = %-2d\n", i, data);
		}
		
		printf("删除状态：%d\n\n", StaticQueueDequeue(queue, NULL));
		printf("获取数据元素状态：%d\n\n", StaticQueueFront(queue, &data));
	
		queue = StaticQueueDestroy(queue);
		len = StaticQueueLength(queue);
		printf("len = %d\n\n", len);
	}
	
	return 0;
}