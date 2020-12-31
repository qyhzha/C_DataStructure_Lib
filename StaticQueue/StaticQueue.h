#ifndef __STATICQUEUE_H__
#define __STATICQUEUE_H__

#define deBug() printf("File = %s\nLine = %d\n", __FILE__, __LINE__)

typedef int DataType;

#define __QUEUE_MAX_SIZE 100

#include <stdlib.h>
#include <stdio.h>

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

STRUCT(StaticQueue)
{
	DataType data[__QUEUE_MAX_SIZE];
	int len;
	int front;
	int tail;
};

StaticQueue* StaticQueueCreate(void);
StaticQueue* StaticQueueDestroy(StaticQueue *queue);
int StaticQueueLength(StaticQueue *queue);
int StaticQueueCapacity(StaticQueue *queue);
Bool StaticQueueEnqueue(StaticQueue *queue, DataType data);
Bool StaticQueueDequeue(StaticQueue *queue, DataType *data);
Bool StaticQueueFront(StaticQueue *queue, DataType *data);

#endif 
