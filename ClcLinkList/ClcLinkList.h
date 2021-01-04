#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

typedef struct __ClcLinkList ClcLinkList;

ClcLinkList *ClcLinkListCreate(void);

ClcLinkList *ClcLinkListDestroy(ClcLinkList *list);

int ClcLinkListLength(ClcLinkList *list);

bool ClcLinkListInsert(ClcLinkList *list, int i, void *data);

bool ClcLinkListInsertBack(ClcLinkList *list, void *data);

void *ClcLinkListDelete(ClcLinkList *list, int i);

void *ClcLinkListDeleteBack(ClcLinkList *list);

bool ClcLinkListSet(ClcLinkList *list, int i, void *data);

void *ClcLinkListGet(ClcLinkList *list, int i);

bool ClcLinkListMove(ClcLinkList *list, int i);

bool ClcLinkListEnd(ClcLinkList *list);

void ClcLinkListNext(ClcLinkList *list);

void *ClcLinkListCurrent(ClcLinkList *list);

#define LinkListForEach(list) for(ClcLinkListMove(list, 0); !ClcLinkListEnd(list); ClcLinkListNext(list))

#define LinkListEntry(list, type) (type*)ClcLinkListCurrent(list)

int ClcLinkListFind(ClcLinkList *list, void *data);

#ifdef __cplusplus
}
#endif

#endif
