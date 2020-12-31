今天使用C语言实现二叉树结构。

下面是Main.c文件：

#include <stdio.h>
#include "BTree.h"
#include "Macro.h"

int main()
{
	BTree *tree = BTreeCreate();
	
	if(tree != NULL)
	{
		LinkList *list = NULL;
		BTreeNode *node = NULL;
		BTreeInsertValue(tree, 1, node);
		
		node = BTreeFindValue(tree, 1);
		BTreeInsertValue(tree, 2, node);
		BTreeInsertValue(tree, 3, node);
		
		node = BTreeFindValue(tree, 2);
		BTreeInsertValue(tree, 4, node);
		BTreeInsertValue(tree, 5, node);
		printf("flag = %d\n", BTreeInsertValue(tree, 6, node));
		
		node = BTreeFindValue(tree, 3);
		BTreeInsertValue(tree, 7, node);
		
		node = BTreeFindValue(tree, 5);
		BTreeInsertValue(tree, 8, node);
		BTreeInsertValue(tree, 9, node);
		
		node = BTreeFindValue(tree, 7);
		BTreeInsertValue(tree, 10, node);
		
		node = BTreeFindValue(tree, 11);
		printf("node = %p\n", node);
		printf("flag = %d\n", BTreeInsertValue(tree, 12, node));
		
		list = BTreeTraversal(tree, LevelOrder);
		
		if(list != NULL)
		{
			printf("Tree One: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		node = BTreeRemoveValue(tree, 5);
		node->parent = NULL;
		
		list = LinkListDestroy(list);
		
		list = BTreeTraversal(tree, LevelOrder);
		
		if(list != NULL)
		{
			printf("Tree Two: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		list = LinkListDestroy(list);
		tree = BTreeDestroy(tree);
		
		tree = BTreeCreate();
		BTreeInsertNode(tree, node);
		
		list = BTreeTraversal(tree, LevelOrder);
		
		if(list != NULL)
		{
			printf("Tree Three: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		list = LinkListDestroy(list);
		tree = BTreeDestroy(tree);
	}
	
	return 0;
}

下面是BTree.h文件：

#ifndef __BTREE_H__
#define __BTREE_H__

#include "Macro.h"
#include "LinkList.h"
#include "DynamicQueue.h"

BTree* BTreeCreate();
BTree* BTreeDestroy(BTree *tree);
BTreeNode* BTreeNodeCreate();
BTreeNode* BTreeNodeDestroy(BTreeNode *node);
Bool BTreeInsertNode(BTree *tree, BTreeNode *node);
Bool BTreeInsertValue(BTree *tree, DataType data, BTreeNode *parent);
BTreeNode* BTreeRemoveNode(BTree *tree, BTreeNode *node);
BTreeNode* BTreeRemoveValue(BTree *tree, DataType data);
BTreeNode* BTreeFindNode(BTree *tree, BTreeNode *node);
BTreeNode* BTreeFindValue(BTree *tree, DataType data);
BTreeNode* BTreeNodeFindNode(BTreeNode *root, BTreeNode *node);
BTreeNode* BTreeNodeFindValue(BTreeNode *root, DataType data);
BTreeNode* root(BTree *tree);
int BTreeDegree(BTree *tree);
int BTreeCount(BTree *tree);
int BTreeHeight(BTree *tree);
LinkList* BTreeTraversal(BTree *tree, enum BTTraversal traversal);

#endif

下面是BTree.c文件：

#include "BTree.h"

BTreeNode* BTreeNodeCreate()	//O(1)
{
	BTreeNode *ret = MALLOC(BTreeNode, 1);
	
	if(ret != NULL)
	{
		ret->parent = NULL;
		ret->m_left = NULL;
		ret->m_right = NULL;
	}
	
	return ret;
}

BTreeNode* BTreeNodeDestroy(BTreeNode *node)	//O(n)
{
	if(node != NULL)
	{
		BTreeNodeDestroy(node->m_left);	
		BTreeNodeDestroy(node->m_right);
		
		FREE(node);
	}
	
	return NULL;
}

BTreeNode* BTreeNodeFindNode(BTreeNode *root, BTreeNode *node) //O(n)
{
	BTreeNode *ret = NULL;
	
	if((root != NULL) && (node != NULL))
	{
		if(root == node)
		{
			ret = node;
		}
		else
		{
			ret = BTreeNodeFindNode(root->m_left, node);
			if(ret == NULL) ret = BTreeNodeFindNode(root->m_right, node);
		}
	}
	
	return ret;
}

BTreeNode* BTreeNodeFindValue(BTreeNode *root, DataType data)	//O(n)
{
	BTreeNode *ret = NULL;
	
	if(root != NULL)
	{
		if(root->data == data)
		{
			ret = root;
		}
		else
		{
			ret = BTreeNodeFindValue(root->m_left, data);
			if(ret == NULL) ret = BTreeNodeFindValue(root->m_right, data);
		}
	}
	
	return ret;	
}

static int BTreeNodeDegree(BTreeNode *root)	//O(n)
{
	int ret = -1;
	
	if(root != NULL)
	{
		ret = 0;
		
		if(root->m_left != NULL) ret++;
		if(root->m_right != NULL) ret++;
		
		if(ret < 2)
		{
			int degree = BTreeNodeDegree(root->m_left);
			
			if(degree < 2) 
			{
				degree = BTreeNodeDegree(root->m_right);
				ret = (ret > degree) ? ret : degree;
			}
			else ret = degree;
		}
	}
	
	return ret;
}

static int BTreeNodeCount(BTreeNode *root)	//O(n)
{	
	return (root != NULL) ? BTreeNodeCount(root->m_left) + BTreeNodeCount(root->m_right) + 1 : 0;
}

static int BTreeNodeHeight(BTreeNode *root)		//O(n)
{
	int ret = 0;
	
	if(root != NULL)
	{
		int lheight = BTreeNodeHeight(root->m_left);
		int rheight = BTreeNodeHeight(root->m_right);
		
		ret = ((lheight > rheight) ? lheight : rheight) + 1;
	}
	
	return ret;	
}

static LinkList* BTreeNodePreTraversal(BTreeNode *root, LinkList *list)
{
	if((root != NULL) && (list != NULL))
	{
		LinkListInsert(list, LinkListLength(list), root);
		BTreeNodePreTraversal(root->m_left, list);
		BTreeNodePreTraversal(root->m_right, list);
	}
	
	return list;
}

static LinkList* BTreeNodeInTraversal(BTreeNode *root, LinkList *list)
{
	if((root != NULL) && (list != NULL))
	{
		BTreeNodeInTraversal(root->m_left, list);
		LinkListInsert(list, LinkListLength(list), root);
		BTreeNodeInTraversal(root->m_right, list);
	}
	
	return list;
}

static LinkList* BTreeNodePostTraversal(BTreeNode *root, LinkList *list)
{
	if((root != NULL) && (list != NULL))
	{
		BTreeNodePostTraversal(root->m_left, list);
		BTreeNodePostTraversal(root->m_right, list);
		LinkListInsert(list, LinkListLength(list), root);
	}
	
	return list;
}

static LinkList* BTreeNodeLevelTraversal(BTreeNode *root, LinkList *list)
{
	if((root != NULL) && (list != NULL))
	{
		DynamicQueue *queue = DynamicQueueCreate();		//O(1)
		
		if(queue != NULL)
		{
			DynamicQueueEnqueue(queue, root);			

			while(DynamicQueueLength(queue) > 0)		
			{
				BTreeNode *node;
				DynamicQueueDequeue(queue, &node);
				LinkListInsert(list, LinkListLength(list), node);
				
				if(node->m_left != NULL) DynamicQueueEnqueue(queue, node->m_left);
				if(node->m_right != NULL)DynamicQueueEnqueue(queue, node->m_right);
			}
			
			queue = DynamicQueueDestroy(queue);
		}
	}
	
	return list;	
}

static LinkList* BTreeNodeTraversal(BTreeNode *root, LinkList *list, enum BTTraversal traversal)	//O(n^2)
{
	if((root != NULL) && (list != NULL))
	{
		switch(traversal)
		{
			case PreOrder: 		BTreeNodePreTraversal(root, list); 	break;
			case InOrder:		BTreeNodeInTraversal(root, list);  	break;
			case PostOrder:		BTreeNodePostTraversal(root, list);	break;
			case LevelOrder:	BTreeNodeLevelTraversal(root, list);break;
			default: list = LinkListDestroy(list);
		}
	}
	
	return list;
}

BTree* BTreeCreate()		//O(1)
{
	BTree *ret = MALLOC(BTree, 1);
	
	if(ret != NULL)
	{
		ret->root = NULL;
	}
	
	return ret;
}

BTree* BTreeDestroy(BTree *tree)		//O(n)
{
	if(tree != NULL)
	{
		BTreeNodeDestroy(tree->root);
		FREE(tree);
	}
	
	return NULL;
}

Bool BTreeInsertNode(BTree *tree, BTreeNode *node)		//O(n)
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
			BTreeNode *parent = BTreeFindNode(tree, node->parent);
			
			if(parent != NULL)
			{
				if(parent->m_left == NULL) parent->m_left = node;
				else if(parent->m_right == NULL) parent->m_right = node;
				else ret = false;
			}
			else
			{
				ret = false;
			}
		}
	}
	
	return ret;
}

Bool BTreeInsertValue(BTree *tree, DataType data, BTreeNode *parent)
{
	Bool ret = (tree != NULL);
	
	if(ret)
	{
		BTreeNode *node = BTreeNodeCreate();
		
		if(node != NULL)
		{
			node->data = data;
			node->parent = parent;
			
			ret = BTreeInsertNode(tree, node);
			
			if(ret == false) node = BTreeNodeDestroy(node);
		}
		else
		{
			ret = false;
		}
	}
	
	return ret;
}

BTreeNode* BTreeRemoveNode(BTree *tree, BTreeNode *node)
{
	BTreeNode *ret = NULL;
	
	if((tree != NULL) && (node != NULL))
	{
		if(tree->root == node)
		{
			tree->root = NULL;
			ret = node;
		}
		else
		{
			BTreeNode *n = BTreeFindNode(tree, node);
			
			if(n != NULL)
			{
				if(n->parent->m_left == n) (n->parent->m_left = NULL, ret = n);
				else if(n->parent->m_right == n) (n->parent->m_right = NULL, ret = n);
			}
		}
	}
		
	return ret;
}

BTreeNode* BTreeRemoveValue(BTree *tree, DataType data)
{
	return BTreeRemoveNode(tree, BTreeFindValue(tree, data));	
}

BTreeNode* BTreeFindNode(BTree *tree, BTreeNode *node)
{
	return ((tree != NULL) && (node != NULL)) ? BTreeNodeFindNode(tree->root, node) : NULL;
}

BTreeNode* BTreeFindValue(BTree *tree, DataType data)
{
	return (tree != NULL) ? BTreeNodeFindValue(tree->root, data) : NULL;
}

BTreeNode* root(BTree *tree)
{
	return (tree != NULL) ? tree->root : NULL;
}

int BTreeDegree(BTree *tree)
{
	return (tree != NULL) ? BTreeNodeDegree(tree->root) : -1;
}

int BTreeCount(BTree *tree)
{
	return (tree != NULL) ? BTreeNodeCount(tree->root) : -1;
}

int BTreeHeight(BTree *tree)
{
	return (tree != NULL) ? BTreeNodeHeight(tree->root) : -1;
}

LinkList* BTreeTraversal(BTree *tree, enum BTTraversal traversal)
{
	return (tree != NULL) ? BTreeNodeTraversal(tree->root, LinkListCreate(), traversal) : NULL;
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
Bool DynamicQueueEnqueue(DynamicQueue *queue, BTreeNode *data);
Bool DynamicQueueDequeue(DynamicQueue *queue, BTreeNode **data);
Bool DynamicQueueFront(DynamicQueue *queue, BTreeNode **data);

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

Bool DynamicQueueEnqueue(DynamicQueue *queue, BTreeNode *data)		//O(n)
{
	Bool ret = (queue != NULL);
	
	if(ret)
	{
		ret = LinkListInsert(queue->list, queue->len, data);//O(n)
		if(ret) queue->len++;
	}
	
	return ret;
}

Bool DynamicQueueDequeue(DynamicQueue *queue, BTreeNode **data)		//O(1)
{
	Bool ret = (queue != NULL);
	
	if(ret)
	{
		ret = LinkListDelete(queue->list, 0, data);	//O(1)
		if(ret) queue->len--;
	}
}

Bool DynamicQueueFront(DynamicQueue *queue, BTreeNode **data)			//(1)
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

STRUCT(LLNode)
{
	BTreeNode* data;
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
Bool LinkListInsert(LinkList *list, int i, BTreeNode* data);
Bool LinkListDelete(LinkList *list, int i, BTreeNode* *data);
int LinkListFind(LinkList *list, BTreeNode* data); 
Bool LinkListSet(LinkList *list, int i, BTreeNode* data);
Bool LinkListGet(LinkList *list, int i, BTreeNode* *data);
LLNode* LinkListMove(LinkList *list, int i);
Bool LinkListEnd(LinkList *list);
void LinkListNext(LinkList *list);
BTreeNode* LinkListCurrent(LinkList *list);

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

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

STRUCT(BTreeNode)					
{
	DataType data;
	BTreeNode *parent;
	BTreeNode *m_left;
	BTreeNode *m_right;
};

STRUCT(BTree)
{
	BTreeNode* root;
};
						
#endif