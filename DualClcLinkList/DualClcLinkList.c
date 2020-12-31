#include "DualClcLinkList.h"

static void insert(DCLLNode *node, DCLLNode *pre, DCLLNode *next)	//O(1)
{
	node->next = next;
	node->pre = pre;
	pre->next = node;
	if(next != NULL) next->pre = node;
}

DualClcLinkList* DualClcLinkListCreate(void)					//O(1)
{
	DualClcLinkList *ret = MALLOC(DualClcLinkList, 1);
	
	if(ret != NULL)
	{
		ret->next = NULL;
		ret->m_current = NULL;
		ret->len = 0;
	}
	
	return ret;
}

DualClcLinkList* DualClcLinkListDestroy(DualClcLinkList *list)				//O(n)
{
	if(list != NULL)
	{
		DCLLNode *node = list->next;
		
		if(node != NULL)
		{
			DCLLNode *pre = NULL;
			
			do
			{
				pre = node;
				node = node->next;
				FREE(pre);			
			}while((node != NULL) && (node != list->next));
		}
		
		FREE(list);
	}
	
	return NULL;
}

int DualClcLinkListLength(DualClcLinkList *list)		//O(1)
{
	return (list != NULL) ? list->len : -1;
}

Bool DualClcLinkListInsert(DualClcLinkList *list, int i, DataType data)		//O(n)
{
	Bool ret = (list != NULL);
	int length = DualClcLinkListLength(list);

	i = ((length >= 0) && (i >= 0)) ? (i % (length + 1)) : -1;
	ret = ret && (i >= 0);
	
	if(ret)
	{
		DCLLNode *node = NULL;
		ret = (((node = MALLOC(DCLLNode, 1)) != NULL) ? true : false);
		
		if(ret)
		{
			node->data = data;
			
			if(0 == i)
			{					
				if(list->next == NULL)
				{
					node->next = node;
					node->pre = node;
				}
				else
				{
					insert(node, DualClcLinkListMove(list, length - 1), list->next);
				}

				list->next = node;
			}
			else
			{								
				DCLLNode *pre = DualClcLinkListMove(list, i - 1);											
				insert(node, pre, pre->next);
			}	

			list->len++;
		}
	}
	
	return ret;
}

Bool DualClcLinkListDelete(DualClcLinkList *list, int i, DataType *data)		//O(n)
{
	Bool ret = 0;
	int length = DualClcLinkListLength(list);
	
	i = ((length >= 0) && (i >= 0)) ? (i % length) : -1;
	ret = (i >= 0);
	
	if(ret)
	{
		DCLLNode *node = list->next;
			
		if(data != NULL) *data = node->data;
		
		if(0 == i)
		{			
			if(node->next == node) list->next = NULL;
			else
			{
				DCLLNode *pre = DualClcLinkListMove(list, length - 1);
				pre->next = node->next;	
				node->next->pre = pre;
				list->next = node->next;
			}
		}
		else
		{	
			DCLLNode *pre = DualClcLinkListMove(list, i - 1);

			pre->next = node->next;	
			node->next->pre = pre;
		}
		
		free(node);
		
		list->len--;
	}
	
	return ret;
}

Bool DualClcLinkListSet(DualClcLinkList *list, int i, DataType data)	//O(n)
{
	Bool ret = (list != NULL);
	int length = DualClcLinkListLength(list);
	
	i = (length >= 0) ? (i % length) : -1;
	ret = ret && (i >= 0);
	
	if(ret)
	{		
		DualClcLinkListMove(list, i)->data = data;
	}
	
	return ret;	
}

Bool DualClcLinkListGet(DualClcLinkList *list, int i, DataType *data)	//O(n)
{
	Bool ret = (list != NULL) && (data != NULL);
	int length = DualClcLinkListLength(list);
	
	i = (length >= 0) ? (i % length) : -1;
	ret = ret && (i >= 0);
	
	if(ret)
	{		
		*data = DualClcLinkListMove(list, i)->data;
	}
	
	return ret;
}

//以下5个函数配合使用以完成对链表的遍历，时间复杂度O(n)
DCLLNode* DualClcLinkListMove(DualClcLinkList *list, int i)	
{
	DCLLNode *ret = NULL;
	int length = DualClcLinkListLength(list);
	
	i = (length >= 0) ? (i % length) : -1;
	
	list->m_current = NULL;
	
	if((list != NULL) && (0 <= i))
	{
		int j;
		ret = list->next;
		
		for(j = 0; j < i; j++)
		{
			ret = ret->next;
		}
		
		list->m_current = ret;
	}
	
	return ret;
}

Bool DualClcLinkListEnd(DualClcLinkList *list)		
{
	return (list != NULL) ? (list->m_current == NULL) : false;
}

void DualClcLinkListNext(DualClcLinkList *list)	
{
	if((list != NULL) && (list->m_current != NULL))
	{
		list->m_current = list->m_current->next;
	}
}

void DualClcLinkListPre(DualClcLinkList *list)		
{
	if((list != NULL) && (list->m_current != NULL))
	{
		list->m_current = list->m_current->pre;
	}	
}

DataType DualClcLinkListCurrent(DualClcLinkList *list)
{
	return ((list != NULL) && (list->m_current != NULL)) ? list->m_current->data : (DataType)0;
}

int DualClcLinkListFind(DualClcLinkList *list, DataType data)	//O(n)
{
	int ret = -1;
	
	if(list)
	{
		DCLLNode *node = list->next;
		
		if(node != NULL)
		{
			int i = 0;
			do
			{
				if(node->data == data)
				{
					ret = i;
					break;
				}
				
				node = node->next;			
			}while((node != NULL) && (node != list->next));
		}		
	}	
	
	return ret;
}