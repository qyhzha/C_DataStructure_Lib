#include "StaticQueue.h"

StaticQueue* StaticQueueCreate(void)		//O(1)
{
	StaticQueue *ret = MALLOC(StaticQueue, 1);
	
	if(ret)
	{	
		ret->len = 0;
		ret->front = 0;
		ret->tail = 0;
	}
	
	return ret;
}

StaticQueue* StaticQueueDestroy(StaticQueue *queue)	//O(1)
{	
	return FREE(queue);
}

int StaticQueueLength(StaticQueue *queue)		//O(1)
{
	return (queue != NULL) ? queue->len : -1;
}

int StaticQueueCapacity(StaticQueue *queue)		//O(1)
{
	return (queue != NULL) ? __QUEUE_MAX_SIZE : -1;
}

Bool StaticQueueEnqueue(StaticQueue *queue, DataType data)	//O(1)
{
	Bool ret = (queue != NULL) && (queue->len < __QUEUE_MAX_SIZE);
	
	if(ret)
	{
		queue->data[queue->tail] = data;
		
		queue->tail = (queue->tail + 1) % __QUEUE_MAX_SIZE;
		queue->len++;
	}
	
	return ret;
}

Bool StaticQueueDequeue(StaticQueue *queue, DataType *data)	//O(1)
{
	Bool ret = (queue != NULL) && (queue->len > 0);
	
	if(ret)
	{	
		if(data != NULL) *data = queue->data[queue->front];
		
		queue->front = (queue->front + 1) % __QUEUE_MAX_SIZE;
		queue->len--;
	}
	
	return ret;
}

Bool StaticQueueFront(StaticQueue *queue, DataType *data)	//O(1)
{	
	return (((queue != NULL) && (data != NULL) && (queue->len > 0)) ? (*data = queue->data[queue->front], true) : false);
}
