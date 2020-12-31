#include "LinkListVertex.h"

VertexNode* VertexNodeCreate(void)
{
	VertexNode *ret = MALLOC(VertexNode, 1);
	
	if(ret != NULL)
	{
		ret->list = LinkListEdgeCreate();
		
		if(ret->list == NULL)
		{
			FREE(ret);
		}
	}
	
	return ret;
}

VertexNode* VertexNodeDestroy(VertexNode *node)
{	
	if(node != NULL)
	{
		node->list = LinkListEdgeDestroy(node->list);
		
		FREE(node);
	}
	
	return NULL;
}

static LLNodeVertex* LLNodeVertexCreate(void)
{
	return MALLOC(LLNodeVertex, 1);	
}

static LLNodeVertex* LLNodeVertexDestroy(LLNodeVertex *node)
{
	if(node != NULL)
	{
		node->data = VertexNodeDestroy(node->data);
		FREE(node);
	}
	
	return NULL;
}

LinkListVertex* LinkListVertexCreate(void)		//O(1)
{
	LinkListVertex *list = MALLOC(LinkListVertex, 1);
	
	if(list != NULL)
	{
		list->len = 0;
		list->next = NULL;
		list->m_current = NULL;
	}
	
	return list;
}

LinkListVertex* LinkListVertexDestroy(LinkListVertex *list)	//O(n)
{
	if(list != NULL)
	{
		while(list->next != NULL)
		{
			LinkListVertexDelete(list, 0, NULL);
		}
		
		FREE(list);
	}
	
	return NULL;
}

int LinkListVertexLength(LinkListVertex *list)	//O(1)
{
	return (list != NULL) ? list->len : -1;
}

Bool LinkListVertexInsert(LinkListVertex *list, int i, VertexNode *data)		//O(n)
{
	Bool ret = (list != NULL) && (i >= 0) && (i <= LinkListVertexLength(list));
	
	if(ret)
	{
		LLNodeVertex *node = LLNodeVertexCreate();
		
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
				LLNodeVertex *pre = LinkListVertexMove(list, i - 1);
				
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

Bool LinkListVertexDelete(LinkListVertex *list, int i, VertexNode **data)	//O(n)
{
	Bool ret = (i >= 0) && (i < LinkListVertexLength(list));
	
	if(ret)
	{
		LLNodeVertex *node = list->next;
		
		if(0 == i)
		{
			if(data) *data = node->data;
			list->next = node->next;
		}
		else
		{
			LLNodeVertex *pre = LinkListVertexMove(list, i - 1);
			
			node = pre->next;
			
			if(data != NULL) *data = node->data;
			
			pre->next = node->next;	
		}
		
		node = LLNodeVertexDestroy(node);
		list->len--;
	}
	
	return ret;
}

Bool LinkListVertexSet(LinkListVertex *list, int i, VertexNode *data)	//O(n)
{
	return ((i >= 0) && (i < LinkListVertexLength(list))) ? (LinkListVertexMove(list, i)->data = data, true) : false;
}

Bool LinkListVertexGet(LinkListVertex *list, int i, VertexNode **data)	//O(n)
{
	return ((data != NULL) && (i >= 0) && (i < LinkListVertexLength(list))) ? (*data = LinkListVertexMove(list, i)->data, true) : false;
}

//下面四个配合使用用于遍历链表，时间复杂度为O(n)
LLNodeVertex* LinkListVertexMove(LinkListVertex *list, int i)
{
	LLNodeVertex *ret = NULL;
	
	list->m_current = NULL;
	
	if((list != NULL) && (i >= 0) && (i < LinkListVertexLength(list)))
	{		
		LLNodeVertex *node = list->next;
		
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

Bool LinkListVertexEnd(LinkListVertex *list)
{
	return (list != NULL) ? (list->m_current == NULL) : false;
}

void LinkListVertexNext(LinkListVertex *list)
{
	if((list != NULL) && (list->m_current != NULL))
	{
		list->m_current = list->m_current->next; 
	}	
}

VertexNode* LinkListVertexCurrent(LinkListVertex *list)
{
	return list->m_current->data;
}

int LinkListVertexFind(LinkListVertex *list, VertexNode *data)	//O(n)
{
	int ret = -1;		
	
	if(list)
	{
		int i = 0;
		
		for(LinkListVertexMove(list, 0); !LinkListVertexEnd(list); LinkListVertexNext(list), i++)
		{
			if(LinkListVertexCurrent(list) == data)
			{
				ret = i;
				break;
			}
		}		
	}
	
	return ret;
}
