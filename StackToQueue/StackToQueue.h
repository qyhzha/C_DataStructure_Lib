#ifndef __STACKTOQUEUE_H__
#define __STACKTOQUEUE_H__

#include "DynamicStack.h"
#include "Macro.h"
#include <stdlib.h>

STRUCT(StackToQueue)
{
	DynamicStack* head1;
	DynamicStack* head2;
	int len;
};

StackToQueue* StackToQueueCreate();
StackToQueue* StackToQueueDestroy(StackToQueue* head);
int StackToQueueLength(StackToQueue* head);
Bool StackToQueueEnqueue(StackToQueue* head, DataType data);
Bool StackToQueueDequeue(StackToQueue* head, DataType* data);
Bool StackToQueueFront(StackToQueue* head, DataType* data);

#endif