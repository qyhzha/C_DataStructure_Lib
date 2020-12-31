#include "LinkList.h"

STRUCT(LLNode)
{
	void *data;
	LLNode *next;
};

struct __LinkList
{
	int len;
	LLNode *next;
	LLNode *m_current;
};

static LLNode *move(LinkList *list, int i)
{
	if((i >= 0) && (i < LinkListLength(list)))
	{	
		LLNode *node = list->next;
		
		int j;			
		for(j = 0; j < i; j++)
		{
			node = node->next;	
		}
			
		return node;		
	}

	return NULL;
}

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
			LinkListDelete(list, 0);
		}
		
		FREE(list);
	}
	
	return NULL;
}

int LinkListLength(LinkList *list)	//O(1)
{
	return (list != NULL) ? list->len : -1;
}

bool LinkListInsert(LinkList *list, int i, void *data)		//O(n)
{
	bool ret = (i >= 0) && (i <= LinkListLength(list));
	
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
				LLNode *pre = move(list, i - 1);
				
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

bool LinkListDelete(LinkList *list, int i)	//O(n)
{
	bool ret = (i >= 0) && (i < LinkListLength(list));
	
	if(ret)
	{
		LLNode *node = list->next;
		
		if(0 == i)
		{
			FREE(node->data);
			list->next = node->next;
		}
		else
		{
			LLNode *pre = move(list, i - 1);
			
			node = pre->next;
			
			FREE(node->data);
			
			pre->next = node->next;	
		}
		
		FREE(node);
		list->len--;
	}
	
	return ret;
}

bool LinkListSet(LinkList *list, int i, void *data)	//O(n)
{
	return ((i >= 0) && (i < LinkListLength(list))) ? (move(list, i)->data = data, true) : false;
}

void *LinkListGet(LinkList *list, int i)	//O(n)
{
	return ((i >= 0) && (i < LinkListLength(list))) ? (move(list, i)->data) : NULL;
}

//下面四个配合使用用于遍历链表，时间复杂度为O(n)
bool LinkListMove(LinkList *list, int i)
{
	return ((i >= 0) && (i < LinkListLength(list))) ? (list->m_current = move(list, i), true) : false;
}

bool LinkListEnd(LinkList *list)
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

void *current(LinkList *list)
{
	return ((list != NULL) && (list->m_current != NULL)) ? list->m_current->data : NULL;
}

int LinkListFind(LinkList *list, void *data)	//O(n)
{
	int ret = -1;		
	
	if(list != NULL && NULL != data)
	{
		int i = 0;
		
		for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list), i++)
		{
			if(current(list) == data)
			{
				ret = i;
				break;
			}
		}		
	}
	
	return ret;
}
