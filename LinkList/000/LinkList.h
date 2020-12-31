#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef int DataType;

#include <stdbool.h>

typedef struct __LinkList LinkList;

LinkList *LinkListCreate(void);
LinkList *LinkListDestroy(LinkList *list);
int LinkListLength(LinkList *list);
bool LinkListInsert(LinkList *list, int i, DataType data);
bool LinkListDelete(LinkList *list, int i, DataType *data);
int LinkListFind(LinkList *list, DataType data);
bool LinkListSet(LinkList *list, int i, DataType data);
bool LinkListGet(LinkList *list, int i, DataType *data);
bool LinkListMove(LinkList *list, int i);
bool LinkListEnd(LinkList *list);
void LinkListNext(LinkList *list);
DataType LinkListCurrent(LinkList *list);

#endif
