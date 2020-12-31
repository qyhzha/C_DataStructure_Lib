#include "DynamicQueue.h"

DynamicQueue* DynamicQueueCreate(void)								//O(1)
{
	DynamicQueue *ret = MALLOC(DynamicQueue, 1);

	if(ret != NULL)
	{
		ret->list = LinkListCreate(); 	//O(1)
		
		if(ret->list != NULL)
		{
			ret->len = 0;
		}
		else
		{
			free(ret);
			ret = NULL;
		}
	}
	
	return ret;
}

DynamicQueue* DynamicQueueDestroy(DynamicQueue *queue)				//O(n)
{
	if(queue != NULL)
	{
		LinkListDestroy(queue->list);	//O(n)
		free(queue);
	}
	
	return NULL;
}

int DynamicQueueLength(DynamicQueue *queue)							//O(1)
{
	return (queue != NULL) ? queue->len : -1;
}

Bool DynamicQueueEnqueue(DynamicQueue *queue, DataType data)		//O(n)
{
	Bool ret = (queue != NULL);
	
	if(ret)
	{
		ret = LinkListInsert(queue->list, queue->len, data);//O(n)
		if(ret) queue->len++;
	}
	
	return ret;
}

Bool DynamicQueueDequeue(DynamicQueue *queue, DataType *data)		//O(1)
{
	Bool ret = (queue != NULL);
	
	if(ret)
	{
		ret = LinkListDelete(queue->list, 0, data);	//O(1)
		if(ret) queue->len--;
	}
}

Bool DynamicQueueFront(DynamicQueue *queue, DataType *data)			//(1)
{
	Bool ret = (queue != NULL) && (data != NULL);
	
	if(ret)
	{
		ret = LinkListGet(queue->list, 0, data);
	}
	
	return ret;
}