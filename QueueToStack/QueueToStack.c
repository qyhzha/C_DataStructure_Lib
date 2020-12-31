#include "QueueToStack.h"

QueueToStack* QueueToStackCreate(void)		//O(1)
{
	QueueToStack *ret = MALLOC(QueueToStack, 1);
	
	if(ret)
	{
		ret->queue1 = DynamicQueueCreate();
		ret->queue2 = DynamicQueueCreate();
		
		if((ret->queue1 != NULL) && (ret->queue2 != NULL))
		{
			ret->len = 0;
		}
		else
		{
			DynamicQueueDestroy(ret->queue1);
			DynamicQueueDestroy(ret->queue2);
			
			FREE(ret);
		}
	}
	
	return ret;
}

QueueToStack* QueueToStackDestroy(QueueToStack *stack)		//O(n)
{
	if(stack != NULL)
	{
		DynamicQueueDestroy(stack->queue1);
		DynamicQueueDestroy(stack->queue2);
			
		FREE(stack);		
	}
	
	return NULL;
}

int QueueToStackLength(QueueToStack *stack)		//O(1)
{
	return (stack != NULL) ? stack->len : -1;	
}

Bool QueueToStackPush(QueueToStack *stack, DataType data)		//O(n)
{
	Bool ret = (stack != NULL);
	
	if(ret)
	{
		ret = DynamicQueueEnqueue(stack->queue1, data);
		if(ret) stack->len++;
	}
	
	return ret;
}

Bool QueueToStackPop(QueueToStack *stack, DataType *data)		//O(n^2)
{
	Bool ret = (stack != NULL);
	
	if(ret)
	{
		while(DynamicQueueLength(stack->queue1) > 1)
		{
			DataType data;
			ret = ret && DynamicQueueDequeue(stack->queue1, &data);
			ret = ret && DynamicQueueEnqueue(stack->queue2, data);
		}
		
		ret = ret && DynamicQueueDequeue(stack->queue1, data);
		
		while(DynamicQueueLength(stack->queue2) > 0)
		{
			DataType data;
			ret = ret && DynamicQueueDequeue(stack->queue2, &data);
			ret = ret && DynamicQueueEnqueue(stack->queue1, data);			
		}
		
		if(ret) stack->len--;
	}
	
	return ret;
}

Bool QueueToStackTop(QueueToStack *stack, DataType *data)		//O(n^2)
{
	Bool ret = ((stack != NULL) && (data != NULL));
	
	if(ret)
	{
		while(DynamicQueueLength(stack->queue1) > 1)
		{
			DataType data;
			ret = ret && DynamicQueueDequeue(stack->queue1, &data);
			ret = ret && DynamicQueueEnqueue(stack->queue2, data);
		}
		
		ret = ret && DynamicQueueDequeue(stack->queue1, data);
		ret = ret && DynamicQueueEnqueue(stack->queue2, *data);
		
		while(DynamicQueueLength(stack->queue2) > 0)
		{
			DataType data;
			ret = ret && DynamicQueueDequeue(stack->queue2, &data);
			ret = ret && DynamicQueueEnqueue(stack->queue1, data);			
		}
	}
	
	return ret;	
}