今天使用之前实现的栈实现队列。

下面是Main.c文件：

#include "StackToQueue.h"
#include <stdio.h>

int main()
{
	StackToQueue* queue = StackToQueueCreate();
	
	if(queue != NULL)
	{
		int i, len = -1, data = -1;
		
		for(i = 0; i < 100; i++)
		{
			StackToQueueEnqueue(queue, i);
		}
		
		len = StackToQueueLength(queue);
		printf("len = %d\n\n", len);
		
		for(i = 0; i < len / 2; i++)
		{
			StackToQueueDequeue(queue, NULL);
		}
		
		len = StackToQueueLength(queue);
		printf("len = %d\n\n", len);
		
		printf("打印队列中元素：\n");
		for(i = 0; i < len; i++)
		{
			int data;
			StackToQueueDequeue(queue, &data);
			printf("queue[%02d] = %-2d\n", i, data);
		}
		
		printf("\n删除状态：%d\n\n", StackToQueueDequeue(queue, NULL));
		printf("获取数据元素状态：%d\n\n", StackToQueueFront(queue, &data));
	
		queue = StackToQueueDestroy(queue);
		len = StackToQueueLength(queue);
		printf("len = %d\n\n", len);
	}
	
	return 0;
}

下面是StackToQueue.h文件：

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

下面是StackToQueue.c文件：

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

下面是DynamicStack.h文件：

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

下面是DynamicStack.c文件：

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

下面是LinkList.h文件：

#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef int DataType;

#define deBug() printf("File = %s\nLine = %d\n", __FILE__, __LINE__)

#include <stdlib.h>

#ifndef __cplusplus
	typedef int Bool;
	#define true 1
	#define false 0
#else
	typedef bool Bool;
#endif

#define MALLOC(type, size)	(type*)malloc(sizeof(type) * size)
#define FREE(p)				(free(p), p = NULL)

#define STRUCT(type) 	typedef struct __struct##type type;\
						struct __struct##type 

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