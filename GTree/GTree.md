今天使用C语言实现通用树结构。

下面是Main.c文件：

#include <stdio.h>
#include "GTree.h"

int main()
{
	GTree *tree = GTreeCreate();
	
	if(tree != NULL)
	{
		LinkList* list = NULL;
		GTreeNode *node = NULL;
		GTreeInsertValue(tree, 1, node);
		
		node = GTreeFindValue(tree, 1);
		GTreeInsertValue(tree, 2, node);
		GTreeInsertValue(tree, 3, node);
		
		node = GTreeFindValue(tree, 2);
		GTreeInsertValue(tree, 4, node);
		GTreeInsertValue(tree, 5, node);
		GTreeInsertValue(tree, 6, node);
		
		node = GTreeFindValue(tree, 3);
		GTreeInsertValue(tree, 7, node);
		
		node = GTreeFindValue(tree, 5);
		GTreeInsertValue(tree, 8, node);
		GTreeInsertValue(tree, 9, node);
		
		node = GTreeFindValue(tree, 7);
		GTreeInsertValue(tree, 10, node);
		
		node = GTreeFindValue(tree, 11);
		printf("node = %p\n", node);
		printf("flag = %d\n", GTreeInsertValue(tree, 12, node));
		
		list = GTreeTraversal(tree);
		
		if(list != NULL)
		{
			printf("Tree One: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		node = GTreeRemoveValue(tree, 5);
		node->parent = NULL;
		
		list = LinkListDestroy(list);
		
		list = GTreeTraversal(tree);
		
		if(list != NULL)
		{
			printf("Tree Two: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		list = LinkListDestroy(list);
		tree = GTreeDestroy(tree);
		
		tree = GTreeCreate();
		GTreeInsertNode(tree, node);
		
		list = GTreeTraversal(tree);
		
		if(list != NULL)
		{
			printf("Tree Three: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		list = LinkListDestroy(list);
		tree = GTreeDestroy(tree);
	}
	
	return 0;
}

下面是GTree.h文件：

#ifndef __GTREE_H__
#define __GTREE_H__

#include "Macro.h"
#include "LinkList.h"
#include "DynamicQueue.h"

STRUCT(GTree)
{
	GTreeNode* root;
};

GTree* GTreeCreate();
GTree* GTreeDestroy(GTree *tree);
GTreeNode* GTreeNodeCreate();
GTreeNode* GTreeNodeDestroy(GTreeNode *node);
Bool GTreeInsertNode(GTree *tree, GTreeNode *node);
Bool GTreeInsertValue(GTree *tree, DataType data, GTreeNode *parent);
GTreeNode* GTreeRemoveNode(GTree *tree, GTreeNode *node);
GTreeNode* GTreeRemoveValue(GTree *tree, DataType data);
GTreeNode* GTreeFindNode(GTree *tree, GTreeNode *node);
GTreeNode* GTreeFindValue(GTree *tree, DataType data);
GTreeNode* GTreeNodeFindNode(GTreeNode *root, GTreeNode *node);
GTreeNode* GTreeNodeFindValue(GTreeNode *root, DataType data);
GTreeNode* root(GTree *tree);
int GTreeDegree(GTree *tree);
int GTreeCount(GTree *tree);
int GTreeHeight(GTree *tree);
LinkList* GTreeTraversal(GTree *tree);

#endif

下面是GTree.c文件：

#include "GTree.h"

GTreeNode* GTreeNodeCreate()	//O(1)
{
	GTreeNode *ret = MALLOC(GTreeNode, 1);
	
	if(ret != NULL)
	{
		ret->list = LinkListCreate();//O(1)
		
		if(ret->list != NULL)
		{
			ret->parent = NULL;
		}
		else
		{
			FREE(ret);
		}
	}
	
	return ret;
}

GTreeNode* GTreeNodeDestroy(GTreeNode *node)	//O(n)
{
	if(node != NULL)
	{
		if(node->list != NULL)
		{
			for(LinkListMove(node->list, 0); !LinkListEnd(node->list); LinkListNext(node->list)) //O(n)
			{
				GTreeNodeDestroy(LinkListCurrent(node->list));	//O()
			}
			
			node->list = LinkListDestroy(node->list);	//O(n)
		}
		
		FREE(node);
	}
	
	return NULL;
}

GTreeNode* GTreeNodeFindNode(GTreeNode *root, GTreeNode *node) //O(n)
{
	GTreeNode *ret = NULL;
	
	if((root != NULL) && (node != NULL))
	{
		if(root == node)
		{
			ret = node;
		}
		else
		{
			for(LinkListMove(root->list, 0); !LinkListEnd(root->list) && (ret == NULL); LinkListNext(root->list))
			{
				ret = GTreeNodeFindNode(LinkListCurrent(root->list), node);	
			}
		}
	}
	
	return ret;
}

GTreeNode* GTreeNodeFindValue(GTreeNode *root, DataType data)	//O(n)
{
	GTreeNode *ret = NULL;
	
	if(root != NULL)
	{
		if(root->data == data)
		{
			ret = root;
		}
		else
		{
			for(LinkListMove(root->list, 0); !LinkListEnd(root->list) && (ret == NULL); LinkListNext(root->list))
			{
				ret = GTreeNodeFindValue(LinkListCurrent(root->list), data);	
			}
		}
	}
	
	return ret;	
}

static int GTreeNodeDegree(GTreeNode *root)	//O(n)
{
	int ret = 0;
	
	if(root != NULL)
	{
		ret = LinkListLength(root->list);
		
		for(LinkListMove(root->list, 0); !LinkListEnd(root->list); LinkListNext(root->list))
		{
			int degree = GTreeNodeDegree(LinkListCurrent(root->list));
			
			if(degree > ret)
			{
				ret = degree;
			}
		}
	}
	
	return ret;
}

static int GTreeNodeCount(GTreeNode *root)	//O(n)
{
	int ret = 0;
	
	if(root != NULL)
	{
		ret = LinkListLength(root->list);
		
		for(LinkListMove(root->list, 0); !LinkListEnd(root->list); LinkListNext(root->list))
		{			
			ret += GTreeNodeCount(LinkListCurrent(root->list));
		}
	}
	
	return ret;
}

static int GTreeNodeHeight(GTreeNode *root)		//O(n)
{
	int ret = 0;
	
	if(root != NULL)
	{
		for(LinkListMove(root->list, 0); !LinkListEnd(root->list); LinkListNext(root->list))
		{
			int height = GTreeNodeHeight(LinkListCurrent(root->list));
			
			if(height > ret)
			{
				ret = height;
			}
		}
		
		ret++;
	}
	
	return ret;	
}

static LinkList* GTreeNodeTraversal(GTreeNode *root, LinkList *list)	//O(n^2)
{
	if((root != NULL) && (list != NULL))
	{
		DynamicQueue *queue = DynamicQueueCreate();		//O(1)
		
		if(queue != NULL)
		{
			DynamicQueueEnqueue(queue, root);			//O(1)
			
			while(DynamicQueueLength(queue) > 0)		//O()
			{
				GTreeNode *node;
				DynamicQueueDequeue(queue, &node);
				LinkListInsert(list, LinkListLength(list), node);
				
				for(LinkListMove(node->list, 0); !LinkListEnd(node->list); LinkListNext(node->list))
				{
					DynamicQueueEnqueue(queue, LinkListCurrent(node->list));
				}
			}
			
			queue = DynamicQueueDestroy(queue);
		}
	}
	
	return list;
}

GTree* GTreeCreate()		//O(1)
{
	GTree *ret = MALLOC(GTree, 1);
	
	if(ret != NULL)
	{
		ret->root = NULL;
	}
	
	return ret;
}

GTree* GTreeDestroy(GTree *tree)		//O(n)
{
	if(tree != NULL)
	{
		GTreeNodeDestroy(tree->root);
		FREE(tree);
	}
	
	return NULL;
}

Bool GTreeInsertNode(GTree *tree, GTreeNode *node)		//O(n)
{
	Bool ret = (tree != NULL) && (node != NULL);
	
	if(ret)
	{
		if(node->parent == NULL)
		{
			if(tree->root == NULL)
			{
				tree->root = node;
			}
			else
			{
				ret = false;
			}
		}
		else
		{
			GTreeNode *parent = GTreeFindNode(tree, node->parent);
			
			if(parent != NULL)
			{
				ret = LinkListInsert(parent->list, LinkListLength(parent->list), node);
			}
			else
			{
				ret = false;
			}
		}
	}
	
	return ret;
}

Bool GTreeInsertValue(GTree *tree, DataType data, GTreeNode *parent)
{
	Bool ret = (tree != NULL);
	
	if(ret)
	{
		GTreeNode *node = GTreeNodeCreate();
		
		if(node != NULL)
		{
			node->data = data;
			node->parent = parent;
			
			ret = GTreeInsertNode(tree, node);
			
			if(ret == false) node = GTreeNodeDestroy(node);
		}
		else
		{
			ret = false;
		}
	}
	
	return ret;
}

GTreeNode* GTreeRemoveNode(GTree *tree, GTreeNode *node)
{
	GTreeNode *ret = NULL;
	
	if((tree != NULL) && (node != NULL))
	{
		if(tree->root == node)
		{
			tree->root = NULL;
			ret = node;
		}
		else
		{
			GTreeNode *n = GTreeFindNode(tree, node);
			
			if(n != NULL)
			{
				int index = LinkListFind(n->parent->list, node);
				
				if(index >= 0)
				{
					LinkListDelete(n->parent->list, index, NULL);
					ret = node;					
				}
			}
		}
	}
		
	return ret;
}

GTreeNode* GTreeRemoveValue(GTree *tree, DataType data)
{
	return GTreeRemoveNode(tree, GTreeFindValue(tree, data));	
}

GTreeNode* GTreeFindNode(GTree *tree, GTreeNode *node)
{
	return ((tree != NULL) && (node != NULL)) ? GTreeNodeFindNode(tree->root, node) : NULL;
}

GTreeNode* GTreeFindValue(GTree *tree, DataType data)
{
	return (tree != NULL) ? GTreeNodeFindValue(tree->root, data) : NULL;
}

GTreeNode* root(GTree *tree)
{
	return (tree != NULL) ? tree->root : NULL;
}

int GTreeDegree(GTree *tree)
{
	return (tree != NULL) ? GTreeNodeDegree(tree->root) : -1;
}

int GTreeCount(GTree *tree)
{
	return (tree != NULL) ? GTreeNodeCount(tree->root) : -1;
}

int GTreeHeight(GTree *tree)
{
	return (tree != NULL) ? GTreeNodeHeight(tree->root) : -1;
}

LinkList* GTreeTraversal(GTree *tree)
{
	return (tree != NULL) ? GTreeNodeTraversal(tree->root, LinkListCreate()) : NULL;
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
Bool DynamicQueueEnqueue(DynamicQueue *queue, GTreeNode *data);
Bool DynamicQueueDequeue(DynamicQueue *queue, GTreeNode **data);
Bool DynamicQueueFront(DynamicQueue *queue, GTreeNode **data);

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

Bool DynamicQueueEnqueue(DynamicQueue *queue, GTreeNode *data)		//O(n)
{
	Bool ret = (queue != NULL);
	
	if(ret)
	{
		ret = LinkListInsert(queue->list, queue->len, data);//O(n)
		if(ret) queue->len++;
	}
	
	return ret;
}

Bool DynamicQueueDequeue(DynamicQueue *queue, GTreeNode **data)		//O(1)
{
	Bool ret = (queue != NULL);
	
	if(ret)
	{
		ret = LinkListDelete(queue->list, 0, data);	//O(1)
		if(ret) queue->len--;
	}
}

Bool DynamicQueueFront(DynamicQueue *queue, GTreeNode **data)			//(1)
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

typedef struct __structGTreeNode GTreeNode;

STRUCT(LLNode)
{
	GTreeNode* data;
	LLNode *next;
};

STRUCT(LinkList)
{
	int len;
	LLNode *next;
	LLNode *m_current;
};

struct __structGTreeNode
{
	DataType data;
	GTreeNode *parent;
	LinkList *list;
};

LinkList* LinkListCreate(void);
LinkList* LinkListDestroy(LinkList *list);
int LinkListLength(LinkList *list);
Bool LinkListInsert(LinkList *list, int i, GTreeNode* data);
Bool LinkListDelete(LinkList *list, int i, GTreeNode* *data);
int LinkListFind(LinkList *list, GTreeNode* data); 
Bool LinkListSet(LinkList *list, int i, GTreeNode* data);
Bool LinkListGet(LinkList *list, int i, GTreeNode* *data);
LLNode* LinkListMove(LinkList *list, int i);
Bool LinkListEnd(LinkList *list);
void LinkListNext(LinkList *list);
GTreeNode* LinkListCurrent(LinkList *list);

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

Bool LinkListInsert(LinkList *list, int i, GTreeNode *data)		//O(n)
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

Bool LinkListDelete(LinkList *list, int i, GTreeNode **data)	//O(n)
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

Bool LinkListSet(LinkList *list, int i, GTreeNode *data)	//O(n)
{
	return ((i >= 0) && (i < LinkListLength(list))) ? (LinkListMove(list, i)->data = data, true) : false;
}

Bool LinkListGet(LinkList *list, int i, GTreeNode **data)	//O(n)
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

GTreeNode* LinkListCurrent(LinkList *list)
{
	return ((list != NULL) && (list->m_current != NULL)) ? list->m_current->data : (DataType)0;
}

int LinkListFind(LinkList *list, GTreeNode *data)	//O(n)
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

typedef char DataType;

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