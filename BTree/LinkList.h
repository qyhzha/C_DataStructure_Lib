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
