#include "StackToQueue.h"
#include <stdio.h>

int main()
{
	StackToQueue* queue = StackToQueueCreate();
	
	if(queue != NULL)
	{
		int i, len = -1, data = -1;
		
		for(i = 0; i < 100; i++)
		{
			StackToQueueEnqueue(queue, i);
		}
		
		len = StackToQueueLength(queue);
		printf("len = %d\n\n", len);
		
		for(i = 0; i < len / 2; i++)
		{
			StackToQueueDequeue(queue, NULL);
		}
		
		len = StackToQueueLength(queue);
		printf("len = %d\n\n", len);
		
		printf("��ӡ������Ԫ�أ�\n");
		for(i = 0; i < len; i++)
		{
			int data;
			StackToQueueDequeue(queue, &data);
			printf("queue[%02d] = %-2d\n", i, data);
		}
		
		printf("\nɾ��״̬��%d\n\n", StackToQueueDequeue(queue, NULL));
		printf("��ȡ����Ԫ��״̬��%d\n\n", StackToQueueFront(queue, &data));
	
		queue = StackToQueueDestroy(queue);
		len = StackToQueueLength(queue);
		printf("len = %d\n\n", len);
	}
	
	return 0;
}