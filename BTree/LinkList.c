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

Bool LinkListInsert(LinkList *list, int i, BTreeNode *data)		//O(n)
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

Bool LinkListDelete(LinkList *list, int i, BTreeNode **data)	//O(n)
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

Bool LinkListSet(LinkList *list, int i, BTreeNode *data)	//O(n)
{
	return ((i >= 0) && (i < LinkListLength(list))) ? (LinkListMove(list, i)->data = data, true) : false;
}

Bool LinkListGet(LinkList *list, int i, BTreeNode **data)	//O(n)
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

BTreeNode* LinkListCurrent(LinkList *list)
{
	return ((list != NULL) && (list->m_current != NULL)) ? list->m_current->data : (DataType)0;
}

int LinkListFind(LinkList *list, BTreeNode *data)	//O(n)
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
