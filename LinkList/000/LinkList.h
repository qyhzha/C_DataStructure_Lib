#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef int DataType;

#define INVALIDDATA 0xffffffff

#include <stdbool.h>

typedef struct __LinkList LinkList;

LinkList *LinkListCreate(void);

LinkList *LinkListDestroy(LinkList *list);

int LinkListLength(LinkList *list);

bool LinkListInsert(LinkList *list, int i, DataType data);

bool LinkListInsertBack(LinkList *list, DataType data);

bool LinkListDelete(LinkList *list, int i, DataType *data);

bool LinkListDeleteBack(LinkList *list, DataType *data);

int LinkListFind(LinkList *list, DataType data);

bool LinkListSet(LinkList *list, int i, DataType data);

bool LinkListGet(LinkList *list, int i, DataType *data);

DataType LinkListGetData(LinkList *list, int i);

bool LinkListMove(LinkList *list, int i);

bool LinkListEnd(LinkList *list);

void LinkListNext(LinkList *list);

DataType LinkListCurrent(LinkList *list);

#define LinkListForEach(list) for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))

#define LinkListEntry(list) (DataType*)LinkListCurrent(list)

#ifdef __cplusplus
}
#endif

#endif
