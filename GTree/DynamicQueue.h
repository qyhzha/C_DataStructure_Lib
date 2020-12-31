#ifndef __DYNAMICQUEUE_H_
#define __DYNAMICQUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

STRUCT(DynamicQueue)
{
	LinkList *list;
	int len;
};

DynamicQueue* DynamicQueueCreate(void);
DynamicQueue* DynamicQueueDestroy(DynamicQueue *queue);
int DynamicQueueLength(DynamicQueue *queue);
Bool DynamicQueueEnqueue(DynamicQueue *queue, GTreeNode *data);
Bool DynamicQueueDequeue(DynamicQueue *queue, GTreeNode **data);
Bool DynamicQueueFront(DynamicQueue *queue, GTreeNode **data);

#endif
