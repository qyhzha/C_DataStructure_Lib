#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include "Macro.h"

STRUCT(LLNode)
{
	DataType data;
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
Bool LinkListInsert(LinkList *list, int i, DataType data);
Bool LinkListDelete(LinkList *list, int i, DataType *data);
int LinkListFind(LinkList *list, DataType data); 
Bool LinkListSet(LinkList *list, int i, DataType data);
Bool LinkListGet(LinkList *list, int i, DataType *data);
LLNode* LinkListMove(LinkList *list, int i);
Bool LinkListEnd(LinkList *list);
void LinkListNext(LinkList *list);
DataType LinkListCurrent(LinkList *list);

#endif
