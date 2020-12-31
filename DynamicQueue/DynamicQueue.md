#include "DynamicQueue.h"
#include <stdio.h>

int main()
{
	DynamicQueue* queue = DynamicQueueCreate();
	
	if(queue != NULL)
	{
		int i, len = -1, data = -1;
		
		for(i = 0; i < 100; i++)
		{
			DynamicQueueEnqueue(queue, i);
		}
		
		len = DynamicQueueLength(queue);
		printf("len = %d\n\n", len);
		
		for(i = 0; i < len / 2; i++)
		{
			DynamicQueueDequeue(queue, NULL);
		}
		
		len = DynamicQueueLength(queue);
		printf("len = %d\n\n", len);
		
		printf("打印队列中元素：\n");
		for(i = 0; i < len; i++)
		{
			int data;
			DynamicQueueDequeue(queue, &data);
			printf("queue[%02d] = %-2d\n", i, data);
		}
		
		printf("\n删除状态：%d\n\n", DynamicQueueDequeue(queue, NULL));
		printf("获取数据元素状态：%d\n\n", DynamicQueueFront(queue, &data));
	
		queue = DynamicQueueDestroy(queue);
		len = DynamicQueueLength(queue);
		printf("len = %d\n\n", len);
	}
	
	return 0;
}

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


#include "DynamicQueue.h"

DynamicQueue* DynamicQueueCreate(void)//O(1)
{
	DynamicQueue *ret = MALLOC(DynamicQueue, 1);

	if(ret != NULL)
	{
		ret->list = LinkListCreate(); //O(1)
		
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

Bool LinkListDelete(LinkList *list, int i, DataType *data)	//O(n)
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

Bool LinkListGet(LinkList *list, int i, DataType *data)	//O(n)
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
