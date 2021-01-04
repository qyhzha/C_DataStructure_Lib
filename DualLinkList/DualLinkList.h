#ifndef __DUALLINKLIST_H__
#define __DUALLINKLIST_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

typedef struct __DualLinkList DualLinkList;

DualLinkList *DualLinkListCreate(void);

DualLinkList *DualLinkListDestroy(DualLinkList *list);

int DualLinkListLength(DualLinkList *list);

bool DualLinkListInsert(DualLinkList *list, int i, void *data);

bool DualLinkListInsertBack(DualLinkList *list, void *data);

void *DualLinkListDelete(DualLinkList *list, int i);

void *DualLinkListDeleteBack(DualLinkList *list);

int DualLinkListFind(DualLinkList *list, void *data);

bool DualLinkListSet(DualLinkList *list, int i, void *data);

void *DualLinkListGet(DualLinkList *list, int i);

bool DualLinkListMove(DualLinkList *list, int i);

bool DualLinkListEnd(DualLinkList *list);

void DualLinkListNext(DualLinkList *list);

void DualLinkListPre(DualLinkList *list);

void *DualLinkListCurrent(DualLinkList *list);

#define LinkListForEach(list) for(DualLinkListMove(list, 0); !DualLinkListEnd(list); DualLinkListNext(list))

#define LinkListEntry(list, type) (type*)DualLinkListCurrent(list)

#ifdef __cplusplus
}
#endif

#endif
