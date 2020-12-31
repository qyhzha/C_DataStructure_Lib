#include "ClcLinkList.h"							

ClcLinkList* ClcLinkListCreate(void)	//O(1)
{
	ClcLinkList *list = MALLOC(ClcLinkList, 1);
	
	if(list != NULL)
	{
		list->next = NULL;
		list->m_current = NULL;
		list->len = 0;
	}
	
	return list;
}

ClcLinkList* ClcLinkListDestroy(ClcLinkList *list)		//o(n)
{
	if(list != NULL)
	{
		CLLNode *node = list->next;
		
		if(node != NULL)
		{
			CLLNode *pre = NULL;
			
			do
			{
				pre = node;
				node = node->next;
				free(pre);			
			}while((node != NULL) && (node != list->next));
		}
		
		FREE(list);		
	}
	
	return NULL;
}

int ClcLinkListLength(ClcLinkList *list)	//O(1)
{
	return (list != NULL) ? list->len : -1;
}

Bool ClcLinkListInsert(ClcLinkList *list, int i, DataType data)		//O(n)
{
	Bool ret = (list != NULL);
	int length = ClcLinkListLength(list);

	i = ((length >= 0) && (i >= 0)) ? (i % (length + 1)) : -1;
	ret = ret && (i >= 0);
	
	if(ret)
	{
		CLLNode *node = MALLOC(CLLNode, 1);
		
		if(node != NULL)
		{
			if(0 == i)
			{										
				node->data = data;		
				
				if(list->next != NULL) 
				{
					ClcLinkListMove(list, ClcLinkListLength(list) - 1)->next = node;
					node->next = list->next;
				}
				else
				{
					node->next = node;
				}
				
				list->next = node;
			}
			else
			{
				CLLNode *pre = ClcLinkListMove(list, i - 1);
														
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

Bool ClcLinkListDelete(ClcLinkList *list, int i, DataType *data)	//O(n)
{
	Bool ret = (list != NULL);
	int length = ClcLinkListLength(list);
	
	i = ((length >= 0) && (i >= 0)) ? (i % length) : -1;
	ret = ret && (i >= 0);
	
	if(ret)
	{
		CLLNode *node = NULL;
		
		if(0 == i)
		{
			node = list->next;
			
			if(node->next == node) list->next = NULL;
			else
			{ 
				ClcLinkListMove(list, length - 1)->next = node->next;			
				list->next = node->next;
			}				
		}
		else
		{
			CLLNode *pre = ClcLinkListMove(list, i - 1);
			
			node = pre->next;	
			
			pre->next = node->next;			
		}
		
		if(data) *data = node->data;
		
		free(node);
		
		list->len--;
	}
	
	return ret;
}

Bool ClcLinkListSet(ClcLinkList *list, int i, DataType data)	//O(n)
{
	Bool ret = (list != NULL);
	int length = ClcLinkListLength(list);
	
	i = ((length >= 0) && (i >= 0)) ? (i % length) : -1;
	ret = ret && (i >= 0);
	
	if(ret)
	{
		ClcLinkListMove(list, i)->data = data;
	}
	
	return ret;	
}

Bool ClcLinkListGet(ClcLinkList *list, int i, DataType *data)	//O(n)
{
	Bool ret = (list != NULL) && (data != NULL);
	int length = ClcLinkListLength(list);
	
	i = ((length >= 0) && (i >= 0)) ? (i % length) : -1;
	ret = ret && (i >= 0);
	
	if(ret)
	{
		*data = ClcLinkListMove(list, i)->data;
	}
	
	return ret;
}

//下面4个函数配合使用以完成循环链表的遍历，时间复杂度为O(n)
CLLNode *ClcLinkListMove(ClcLinkList *list, int i)
{
	CLLNode *ret = NULL;
	int len = ClcLinkListLength(list);
	
	i = ((len >= 0) && (i >= 0)) ? (i % len) : -1;
	
	list->m_current = NULL;
	
	if((list != NULL) && (i >= 0))
	{		
		ret = list->next;
		
		if(node != NULL)
		{
			int j;
			
			for(j = 0; j < i; j++)
			{
				ret = ret->next;	
			}
			
			list->m_current = node;				
		}	
	}
	
	return ret;
}

Bool ClcLinkListEnd(ClcLinkList *list)
{
	return (list != NULL) ? (list->m_current == NULL) : false;
}

void ClcLinkListNext(ClcLinkList *list)
{
	if((list != NULL) && (list->m_current != NULL))
	{
		list->m_current = list->m_current->next; 
	}
}

DataType ClcLinkListCurrent(ClcLinkList *list)
{
	return ((list != NULL) && (list->m_current != NULL)) ? list->m_current->data : (DataType)0;
}

int ClcLinkListFind(ClcLinkList *list, DataType data)	//O(n)
{
	int ret = -1;
	
	if(list)
	{
		CLLNode *node = list->next;
		
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
			}while(node != list->next);
		}		
	}	
	
	return ret;
}
