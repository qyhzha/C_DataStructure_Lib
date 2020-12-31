#ifndef __STATICSTACK_H_
#define __STATICSTACK_H_

typedef int DataType; 
#define __STATICSTACK_MAX 100

#define deBug() printf("File = %s\nLine = %d\n", __FILE__, __LINE__)

#include <stdio.h>
#include <stdlib.h>

#ifndef __cplusplus
	typedef int Bool;
	#define true 1
	#define false 0
#else
	typedef bool Bool;
#endif

#define MALLOC(type, size) 	(type*)malloc(sizeof(type)  *size)
#define FREE(p)				(free(p), p = NULL)

#define STRUCT(type)	typedef struct __struct##type type;\
						struct __struct##type

STRUCT(StaticStack)
{
	DataType data[__STATICSTACK_MAX];
	int len;
	int top;
};

StaticStack* StaticStackCreate(void);
StaticStack* StaticStackDestroy(StaticStack *stack);
int StaticStacktLength(StaticStack *stack);
int StaticStackCapacity(StaticStack *stack);
Bool StaticStackPush(StaticStack *stack, DataType data);
Bool StaticStackPop(StaticStack *stack, DataType *data);
Bool StaticStackTop(StaticStack *stack, DataType *data);

#endif
