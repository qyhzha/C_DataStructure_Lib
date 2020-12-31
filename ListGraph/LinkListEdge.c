#include "LinkListEdge.h"

LinkListEdge* LinkListEdgeCreate(void)		//O(1)
{
	LinkListEdge *list = MALLOC(LinkListEdge, 1);
	
	if(list != NULL)
	{
		list->len = 0;
		list->next = NULL;
		list->m_current = NULL;
	}
	
	return list;
}

LinkListEdge* LinkListEdgeDestroy(LinkListEdge *list)	//O(n)
{
	if(list != NULL)
	{
		while(list->next != NULL)
		{
			LinkListEdgeDelete(list, 0, NULL);
		}
		
		FREE(list);
	}
	
	return NULL;
}

int LinkListEdgeLength(LinkListEdge *list)	//O(1)
{
	return (list != NULL) ? list->len : -1;
}

Bool LinkListEdgeInsert(LinkListEdge *list, int i, EdgeNode data)		//O(n)
{
	Bool ret = (list != NULL) && (i >= 0) && (i <= LinkListEdgeLength(list));
	
	if(ret)
	{
		LLNodeEdge *node = MALLOC(LLNodeEdge, 1);
		
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
				LLNodeEdge *pre = LinkListEdgeMove(list, i - 1);
				
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

Bool LinkListEdgeDelete(LinkListEdge *list, int i, EdgeNode *data)	//O(n)
{
	Bool ret = (i >= 0) && (i < LinkListEdgeLength(list));
	
	if(ret)
	{
		LLNodeEdge *node = list->next;
		
		if(0 == i)
		{
			if(data != NULL) *data = node->data;
			list->next = node->next;
		}
		else
		{
			LLNodeEdge *pre = LinkListEdgeMove(list, i - 1);
			
			node = pre->next;
			
			if(data != NULL) *data = node->data;
			
			pre->next = node->next;	
		}
		
		free(node);
		list->len--;
	}
	
	return ret;
}

Bool LinkListEdgeSet(LinkListEdge *list, int i, EdgeNode data)	//O(n)
{
	return ((i >= 0) && (i < LinkListEdgeLength(list))) ? (LinkListEdgeMove(list, i)->data = data, true) : false;
}

Bool LinkListEdgeGet(LinkListEdge *list, int i, EdgeNode* data)	//O(n)
{
	return ((data != NULL) && (i >= 0) && (i < LinkListEdgeLength(list))) ? (*data = LinkListEdgeMove(list, i)->data, true) : false;
}

//下面四个配合使用用于遍历链表，时间复杂度为O(n)
LLNodeEdge* LinkListEdgeMove(LinkListEdge *list, int i)
{
	LLNodeEdge *ret = NULL;
	
	list->m_current = NULL;
	
	if((list != NULL) && (i >= 0) && (i < LinkListEdgeLength(list)))
	{		
		LLNodeEdge *node = list->next;
		
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

Bool LinkListEdgeEnd(LinkListEdge *list)
{
	return (list != NULL) ? (list->m_current == NULL) : false;
}

void LinkListEdgeNext(LinkListEdge *list)
{
	if((list != NULL) && (list->m_current != NULL))
	{
		list->m_current = list->m_current->next; 
	}	
}

EdgeNode LinkListEdgeCurrent(LinkListEdge *list)
{
	return list->m_current->data;
}

EdgeNode* LinkListEdgeCurrentPtr(LinkListEdge *list)
{
	return &(list->m_current->data);
}

int LinkListEdgeFind(LinkListEdge *list, int end)	//O(n)
{
	int ret = -1;		
	
	if(list != NULL)
	{
		int i = 0;
		
		for(LinkListEdgeMove(list, 0); !LinkListEdgeEnd(list); LinkListEdgeNext(list), i++)
		{
			if(LinkListEdgeCurrent(list).end == end)
			{
				ret = i;
				break;
			}
		}		
	}
	
	return ret;
}
