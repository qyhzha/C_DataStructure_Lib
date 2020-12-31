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
LinkList* BTreeTraversal(BTree *tree, BTTraversal traversal);

#endif