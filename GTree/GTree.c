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