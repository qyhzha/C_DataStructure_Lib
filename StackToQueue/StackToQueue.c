#include "StackToQueue.h"

StackToQueue* StackToQueueCreate()			//O(n)
{
	StackToQueue* ret = MALLOC(StackToQueue, 1);
	
	if(ret != NULL)
	{
		ret->head1 = DynamicStackCreate();
		ret->head2 = DynamicStackCreate();
		
		if((ret->head1 != NULL) && (ret->head2 != NULL))
		{
			ret->len = 0;
		}
		else
		{
			DynamicStackDestroy(ret->head1);
			DynamicStackDestroy(ret->head2);
			FREE(ret);
		}
	}
	
	return ret;
}

StackToQueue* StackToQueueDestroy(StackToQueue* head)	//O(n)
{
	if(head != NULL)
	{
		DynamicStackDestroy(head->head1);
		DynamicStackDestroy(head->head2);
		
		FREE(head);
	}
	
	return NULL;
}

int StackToQueueLength(StackToQueue* head)		//O(1)
{
	return (head != NULL) ? head->len : -1;
}

Bool StackToQueueEnqueue(StackToQueue* head, DataType data)		//O(1)
{
	Bool ret = (head != NULL);
	
	if(ret)
	{
		ret = DynamicStackPush(head->head1, data);
		if(ret) head->len++;
	}
	
	return ret;
}

Bool StackToQueueDequeue(StackToQueue* head, DataType* data)	//O(n)
{
	Bool ret = (head != NULL);
	
	if(ret)
	{
		while(DynamicStackLength(head->head1) > 0)
		{
			DataType temp;
			ret = ret && DynamicStackPop(head->head1, &temp);
			ret = ret && DynamicStackPush(head->head2, temp);
		}
		
		ret = ret && DynamicStackPop(head->head2, data);
		
		while(DynamicStackLength(head->head2) > 0)
		{
			DataType temp;
			ret = ret && DynamicStackPop(head->head2, &temp);
			ret = ret && DynamicStackPush(head->head1, temp);
		}
		
		if(ret) head->len--;
	}
	
	return ret;
}

Bool StackToQueueFront(StackToQueue* head, DataType* data)		//O(n)
{
	Bool ret = (head != NULL);
	
	if(ret)
	{
		while(DynamicStackLength(head->head1) > 0)
		{
			DataType temp;
			ret = ret && DynamicStackPop(head->head1, &temp);
			ret = ret && DynamicStackPush(head->head2, temp);
		}
		
		ret = ret && DynamicStackTop(head->head2, data);
		
		while(DynamicStackLength(head->head2) > 0)
		{
			DataType temp;
			ret = ret && DynamicStackPop(head->head2, &temp);
			ret = ret && DynamicStackPush(head->head1, temp);
		}
	}
	
	return ret;	
}