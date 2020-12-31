#ifndef __QueueToStack_H__
#define __QueueToStack_H__

#include <stdio.h>
#include <stdlib.h>
#include "DynamicQueue.h"
#include "Macro.h"

STRUCT(QueueToStack)
{
	DynamicQueue *queue1;
	DynamicQueue *queue2;
	int len;
};

QueueToStack* QueueToStackCreate(void);
QueueToStack* QueueToStackDestroy(QueueToStack *stack);
int QueueToStackLength(QueueToStack *stack);
Bool QueueToStackPush(QueueToStack *stack, DataType data);
Bool QueueToStackPop(QueueToStack *stack, DataType *data);
Bool QueueToStackTop(QueueToStack *stack, DataType *data);

#endif
