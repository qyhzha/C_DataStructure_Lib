#include "DynamicStack.h"

DynamicStack* DynamicStackCreate(void)
{
	DynamicStack *stack = MALLOC(DynamicStack, 1);
	
	if(stack != NULL)
	{
		stack->list = LinkListCreate();
		
		if(stack->list != NULL)
		{
			stack->len = 0;
		}
		else
		{
			free(stack);
			stack = NULL;
		}
	}
	
	return stack;
}

DynamicStack* DynamicStackDestroy(DynamicStack *stack)
{
	if(stack != NULL)
	{
		LinkListDestroy(stack->list);
		free(stack);
	}
	
	return NULL;
}

int DynamicStackLength(DynamicStack *stack)
{
	return (stack != NULL) ? stack->len : -1;
}

Bool DynamicStackPush(DynamicStack *stack, DataType data)
{
	Bool ret = (stack != NULL);
	
	if(ret)
	{
		ret = LinkListInsert(stack->list, 0, data);
		
		if(ret)
		{
			stack->len++;
		}
	}
	
	return ret;
}

Bool DynamicStackPop(DynamicStack *stack, DataType *data)
{
	Bool ret = (stack != NULL);
	
	if(ret)
	{
		ret = LinkListDelete(stack->list, 0, data);
		
		if(ret)
		{
			stack->len--;
		}
	}
	
	return ret;
}

Bool DynamicStackTop(DynamicStack *stack, DataType *data)
{
	Bool ret = (stack != NULL) && (data != NULL);
	
	if(ret)
	{
		ret = LinkListGet(stack->list, 0, data);
	}
	
	return ret;
}