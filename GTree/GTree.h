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