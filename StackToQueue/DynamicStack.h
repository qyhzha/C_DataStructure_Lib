#ifndef __DYNAMICSTACK_H__
#define __DYNAMICSTACK_H__

#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

STRUCT(DynamicStack)
{
	LinkList *list;
	int len;
};

DynamicStack* DynamicStackCreate(void);
DynamicStack* DynamicStackDestroy(DynamicStack *stack);
int DynamicStackLength(DynamicStack *stack);
Bool DynamicStackPush(DynamicStack *stack, DataType data);
Bool DynamicStackPop(DynamicStack *stack, DataType *data);
Bool DynamicStackTop(DynamicStack *stack, DataType *data);

#endif
