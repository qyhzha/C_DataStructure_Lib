#include "StaticStack.h"

StaticStack* StaticStackCreate(void)	//O(1)
{
	StaticStack *ret = MALLOC(StaticStack, 1);
	
	if(ret != NULL)
	{
		ret->top = -1;
		ret->len = 0;
	}
	
	return ret;
}

StaticStack* StaticStackDestroy(StaticStack *stack)	//O(1)
{
	return FREE(stack);
}

int StaticStackLength(StaticStack *stack)	//O(1)
{
	return (stack != NULL) ? stack->len : -1;
}

int StaticStackCapacity(StaticStack *stack)		//O(1)
{
	return (stack != NULL) ? __STATICSTACK_MAX : -1;
}

Bool StaticStackPush(StaticStack *stack, DataType data)		//O(1)
{
	Bool ret = (stack != NULL) && (stack->len < __STATICSTACK_MAX);
	
	if(ret)
	{	
		stack->data[stack->len] = data;
		
		stack->top++;
		stack->len++;
	}
	
	return ret;
}

Bool StaticStackPop(StaticStack *stack, DataType *data)		//O(1)
{
	Bool ret = (stack != NULL) && (stack->len > 0);
	
	if(ret)
	{
		if(data != NULL) *data = stack->data[stack->top];
		
		stack->top--;
		stack->len--;
	}
	
	return ret;
}

Bool StaticStackTop(StaticStack *stack, DataType *data)		//(1)
{
	Bool ret = (stack != NULL) && (stack->len > 0);
	
	if(ret)
	{
		if(data != NULL) *data = stack->data[stack->top];
	}
	
	return ret;
}