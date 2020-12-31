#include "DualLinkList.h"

DualLinkList* DualLinkListCreate(void)		//O(1)
{
	DualLinkList *list = MALLOC(DualLinkList, 1);
	
	if(list != NULL)
	{
		list->next = NULL;
		list->m_current = NULL;
		list->len = 0;
	}
	
	return list;
}

DualLinkList* DualLinkListDestroy(DualLinkList *list) 	//O(n)
{	
	if(list != NULL)
	{
		while(list->next != NULL)
		{
			DualLinkListDelete(list, 0, NULL);
		}
			
		FREE(list);		
	}

	return NULL;
}

int DualLinkListLength(DualLinkList *list)	//O(1)
{	
	return (list != NULL) ? list->len : -1;
}

Bool DualLinkListInsert(DualLinkList *list, int i, DataType data)		//O(n)
{
	Bool ret = (i >= 0) && (i <= DualLinkListLength(list));
	
	if(ret)
	{
		DLLNode *node = MALLOC(DLLNode, 1);
		
		if(node)
		{
			node->data = data;
			
			if(0 == i)
			{
				node->next = list->next;
				node->pre = NULL;
				if(list->next != NULL) list->next->pre = node;				
				list->next = node;
			}
			else
			{
				DLLNode *pre = DualLinkListMove(list, i - 1);
				
				node->next = pre->next;
				node->pre  = pre;
				
				if(pre->next != NULL) pre->next->pre = node;
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

Bool DualLinkListDelete(DualLinkList *list, int i, DataType *data)	//O(n)
{
	Bool ret = (i >= 0) && (i < DualLinkListLength(list));
	
	if(ret)
	{
		DLLNode *node = list->next;
		
		if(0 == i)
		{
			if(data) *data = node->data;
			
			list->next = node->next;
			if(node->next != NULL) node->next->pre = NULL;
		}
		else
		{
			DLLNode *pre = DualLinkListMove(list, i - 1);
			
			node = pre->next;
			
			if(data) *data = node->data;
			
			pre->next = node->next;				
			if(node->next != NULL) node->next->pre = pre;
		}
		
		free(node);
		
		list->len--;
	}
	
	return ret;
}

Bool DualLinkListSet(DualLinkList *list, int i, DataType data)	//O(n)
{
	return ((i >= 0) && (i < DualLinkListLength(list))) ? (DualLinkListMove(list, i)->data = data, true) : false;	
}

Bool DualLinkListGet(DualLinkList *list, int i, DataType *data)	//O(n)
{
	return ((data != NULL) && (i >= 0) && (i < DualLinkListLength(list))) ? (*data = DualLinkListMove(list, i)->data, true) : false;
}

//以下五个函数配合使用以遍历双向链表，时间复杂度为O(n)
DLLNode* DualLinkListMove(DualLinkList *list, int i)
{
	DLLNode *ret = NULL;
	
	list->m_current = NULL;
	
	if((list != NULL) && (i >= 0) && (i < DualLinkListLength(list)))
	{		
		DLLNode *node = list->next;
		
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

Bool DualLinkListEnd(DualLinkList *list)
{
	return (list != NULL) ? (list->m_current == NULL) : false;
}

void DualLinkListNext(DualLinkList *list)
{
	if((list != NULL) && (list->m_current != NULL))
	{
		list->m_current = list->m_current->next; 
	}	
}

void DualLinkListPre(DualLinkList *list)
{
	if((list != NULL) && (list->m_current != NULL))
	{
		list->m_current = list->m_current->pre; 
	}		
}

DataType DualLinkListCurrent(DualLinkList *list)
{
	return ((list != NULL) && (list->m_current != NULL)) ? list->m_current->data : (DataType)0;
}

int DualLinkListFind(DualLinkList *list, DataType data)	//O(n)
{
	int ret = -1;		
	
	if(list)
	{
		int i = 0;
		
		for(DualLinkListMove(list, 0); !DualLinkListEnd(list); DualLinkListNext(list), i++)
		{
			if(DualLinkListCurrent(list) == data)
			{
				ret = i;
				break;
			}
		}		
	}
	
	return ret;
}
