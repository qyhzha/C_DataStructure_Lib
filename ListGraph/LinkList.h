#ifndef __LinkList_H__
#define __LinkList_H__

#include "Macro.h"

STRUCT(LLNode)
{
	int data;
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
Bool LinkListInsert(LinkList *list, int i, int data);
Bool LinkListDelete(LinkList *list, int i, int *data);
int LinkListFind(LinkList *list, int data); 
Bool LinkListSet(LinkList *list, int i, int data);
Bool LinkListGet(LinkList *list, int i, int *data);
LLNode* LinkListMove(LinkList *list, int i);
Bool LinkListEnd(LinkList *list);
void LinkListNext(LinkList *list);
int LinkListCurrent(LinkList *list);

#endif
