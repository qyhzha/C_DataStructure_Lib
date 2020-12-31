今天使用之前实现的队列实现栈。

下面是Main.c文件;

#include "QueueToStack.h"
#include <stdio.h>

int main()
{
	QueueToStack* stack = QueueToStackCreate();
	
	if(stack != NULL)
	{
		int i, len = -1, data = -1;
		
		for(i = 0; i < 100; i++)
		{
			QueueToStackPush(stack, i);
		}
		
		len = QueueToStackLength(stack);
		printf("len = %d\n\n", len);
		
		for(i = 0; i < len / 2; i++)
		{
			QueueToStackPop(stack, NULL);
		}
		
		len = QueueToStackLength(stack);
		printf("len = %d\n\n", len);
		
		printf("打印队列中元素：\n");
		for(i = 0; i < len; i++)
		{
			int data;
			QueueToStackPop(stack, &data);
			printf("stack[%02d] = %-2d\n", i, data);
		}
		
		printf("\n删除状态：%d\n\n", QueueToStackPop(stack, NULL));
		printf("获取数据元素状态：%d\n\n", QueueToStackTop(stack, &data));
	
		stack = QueueToStackDestroy(stack);
		len = QueueToStackLength(stack);
		printf("len = %d\n\n", len);
	}
	
	return 0;
}

下面是QueueToStack.h文件：

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


下面是QueueToStack.c文件：

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

下面是DynamicQueue.h文件：

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
Bool DynamicQueueEnqueue(DynamicQueue *queue, DataType data);
Bool DynamicQueueDequeue(DynamicQueue *queue, DataType *data);
Bool DynamicQueueFront(DynamicQueue *queue, DataType *data);

#endif

下面是DynamicQueue.c文件：

#include "DynamicQueue.h"

DynamicQueue* DynamicQueueCreate(void)								//O(1)
{
	DynamicQueue *ret = MALLOC(DynamicQueue, 1);

	if(ret != NULL)
	{
		ret->list = LinkListCreate(); 	//O(1)
		
		if(ret->list != NULL)
		{
			ret->len = 0;
		}
		else
		{
			free(ret);
			ret = NULL;
		}
	}
	
	return ret;
}

DynamicQueue* DynamicQueueDestroy(DynamicQueue *queue)				//O(n)
{
	if(queue != NULL)
	{
		LinkListDestroy(queue->list);	//O(n)
		free(queue);
	}
	
	return NULL;
}

int DynamicQueueLength(DynamicQueue *queue)							//O(1)
{
	return (queue != NULL) ? queue->len : -1;
}

Bool DynamicQueueEnqueue(DynamicQueue *queue, DataType data)		//O(n)
{
	Bool ret = (queue != NULL);
	
	if(ret)
	{
		ret = LinkListInsert(queue->list, queue->len, data);//O(n)
		if(ret) queue->len++;
	}
	
	return ret;
}

Bool DynamicQueueDequeue(DynamicQueue *queue, DataType *data)		//O(1)
{
	Bool ret = (queue != NULL);
	
	if(ret)
	{
		ret = LinkListDelete(queue->list, 0, data);	//O(1)
		if(ret) queue->len--;
	}
}

Bool DynamicQueueFront(DynamicQueue *queue, DataType *data)			//(1)
{
	Bool ret = (queue != NULL) && (data != NULL);
	
	if(ret)
	{
		ret = LinkListGet(queue->list, 0, data);
	}
	
	return ret;
}

下面是LinkList.h文件：

#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include "Macro.h"

STRUCT(LLNode)
{
	DataType data;
	LLNode *next;
};

STRUCT(LinkList)
{
	int len;
	LLNode *next;
	LLNode *m_current;
};

LinkList* LinkListCreate(void);
LinkList* LinkListDestroy(LinkList *list);
int LinkListLength(LinkList *list);
Bool LinkListInsert(LinkList *list, int i, DataType data);
Bool LinkListDelete(LinkList *list, int i, DataType *data);
int LinkListFind(LinkList *list, DataType data); 
Bool LinkListSet(LinkList *list, int i, DataType data);
Bool LinkListGet(LinkList *list, int i, DataType *data);
LLNode* LinkListMove(LinkList *list, int i);
Bool LinkListEnd(LinkList *list);
void LinkListNext(LinkList *list);
DataType LinkListCurrent(LinkList *list);

#endif

下面是LinkList.c文件：

#include "LinkList.h"

LinkList* LinkListCreate(void)		//O(1)
{
	LinkList *list = MALLOC(LinkList, 1);
	
	if(list != NULL)
	{
		list->len = 0;
		list->next = NULL;
		list->m_current = NULL;
	}
	
	return list;
}

LinkList* LinkListDestroy(LinkList *list)	//O(n)
{
	if(list != NULL)
	{
		while(list->next != NULL)
		{
			LinkListDelete(list, 0, NULL);
		}
		
		FREE(list);
	}
	
	return NULL;
}

int LinkListLength(LinkList *list)	//O(1)
{
	return (list != NULL) ? list->len : -1;
}

Bool LinkListInsert(LinkList *list, int i, DataType data)		//O(n)
{
	Bool ret = (list != NULL) && (i >= 0) && (i <= LinkListLength(list));
	
	if(ret)
	{
		LLNode *node = MALLOC(LLNode, 1);
		
		if(node != NULL)
		{			
			if(0 == i)
			{
				node->data = data;
				node->next = list->next;
				
				list->next = node;
			}
			else
			{
				LLNode *pre = LinkListMove(list, i - 1);
				
				node->data = data;
				node->next = pre->next;
				
				pre->next = node;
			}
			
			list->len++;
		}
		else
		{
			ret = false;
		}
	}
	
	return ret;
}

Bool LinkListDelete(LinkList *list, int i, DataType* data)	//O(n)
{
	Bool ret = (i >= 0) && (i < LinkListLength(list));
	
	if(ret)
	{
		LLNode *node = list->next;
		
		if(0 == i)
		{
			if(data) *data = node->data;
			list->next = node->next;
		}
		else
		{
			LLNode *pre = LinkListMove(list, i - 1);
			
			node = pre->next;
			
			if(data) *data = node->data;
			
			pre->next = node->next;	
		}
		
		free(node);
		list->len--;
	}
	
	return ret;
}

Bool LinkListSet(LinkList *list, int i, DataType data)	//O(n)
{
	return ((i >= 0) && (i < LinkListLength(list))) ? (LinkListMove(list, i)->data = data, true) : false;
}

Bool LinkListGet(LinkList *list, int i, DataType* data)	//O(n)
{
	return ((data != NULL) && (i >= 0) && (i < LinkListLength(list))) ? (*data = LinkListMove(list, i)->data, true) : false;
}

//下面四个配合使用用于遍历链表，时间复杂度为O(n)
LLNode* LinkListMove(LinkList *list, int i)
{
	LLNode *ret = NULL;
	
	list->m_current = NULL;
	
	if((list != NULL) && (i >= 0) && (i < LinkListLength(list)))
	{		
		LLNode *node = list->next;
		
		if(node != NULL)
		{
			int j;
			
			for(j = 0; j < i; j++)
			{
				node = node->next;	
			}
			
			ret = node;
			list->m_current = node;				
		}	
	}
	
	return ret;
}

Bool LinkListEnd(LinkList *list)
{
	return (list != NULL) ? (list->m_current == NULL) : false;
}

void LinkListNext(LinkList *list)
{
	if((list != NULL) && (list->m_current != NULL))
	{
		list->m_current = list->m_current->next; 
	}	
}

DataType LinkListCurrent(LinkList *list)
{
	return ((list != NULL) && (list->m_current != NULL)) ? list->m_current->data : (DataType)0;
}

int LinkListFind(LinkList *list, DataType data)	//O(n)
{
	int ret = -1;		
	
	if(list)
	{
		int i = 0;
		
		for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list), i++)
		{
			if(LinkListCurrent(list) == data)
			{
				ret = i;
				break;
			}
		}		
	}
	
	return ret;
}

下面是Macro.h文件：

#ifndef __MACRO_H__
#define __MACRO_H__

typedef int DataType;

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

#define MALLOC(type, size) 	(type*)malloc(sizeof(type) * size)
#define FREE(p)				(free(p), p = NULL)

#define STRUCT(type)	typedef struct __struct##type type;\
						struct __struct##type

#endif

