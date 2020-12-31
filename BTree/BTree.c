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