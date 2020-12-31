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
