#include "QueueToStack.h"
#include <stdio.h>

int main()
{
	QueueToStack* stack = QueueToStackCreate();
	
	if(stack != NULL)
	{
		int i, len = -1, data = -1;
		
		for(i = 0; i < 100; i++)
		{
			QueueToStackPush(stack, i);
		}
		
		len = QueueToStackLength(stack);
		printf("len = %d\n\n", len);
		
		for(i = 0; i < len / 2; i++)
		{
			QueueToStackPop(stack, NULL);
		}
		
		len = QueueToStackLength(stack);
		printf("len = %d\n\n", len);
		
		printf("打印队列中元素：\n");
		for(i = 0; i < len; i++)
		{
			int data;
			QueueToStackPop(stack, &data);
			printf("stack[%02d] = %-2d\n", i, data);
		}
		
		printf("\n删除状态：%d\n\n", QueueToStackPop(stack, NULL));
		printf("获取数据元素状态：%d\n\n", QueueToStackTop(stack, &data));
	
		stack = QueueToStackDestroy(stack);
		len = QueueToStackLength(stack);
		printf("len = %d\n\n", len);
	}
	
	return 0;
}