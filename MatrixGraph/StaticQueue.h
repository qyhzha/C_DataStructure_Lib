#ifndef __STATICQUEUE_H__
#define __STATICQUEUE_H__

#include "Macro.h"

STRUCT(StaticQueue)
{
	int data[__QUEUE_MAX_SIZE];
	int len;
	int front;
	int tail;
};

StaticQueue* StaticQueueCreate(void);
StaticQueue* StaticQueueDestroy(StaticQueue *queue);
int StaticQueueLength(StaticQueue *queue);
int StaticQueueCapacity(StaticQueue *queue);
Bool StaticQueueEnqueue(StaticQueue *queue, int data);
Bool StaticQueueDequeue(StaticQueue *queue, int *data);
Bool StaticQueueFront(StaticQueue *queue, int *data);

#endif 
