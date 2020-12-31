#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#ifdef __cplusplus
extern "C"
{
#else
typedef enum {false, true} bool;
#endif

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(type, size)  ((type*)malloc(sizeof(type) * size))
#define FREE(p)             (free(p), p = NULL)

#define STRUCT(type)    typedef struct __struct##type type;\
                        struct __struct##type

typedef struct __LinkList LinkList;

LinkList *LinkListCreate(void);     //O(1)

LinkList *LinkListDestroy(LinkList *list);  //O(n)

int LinkListLength(LinkList *list); //O(1)

bool LinkListInsert(LinkList *list, int i, void *data); //O(n)

bool LinkListInsertBack(LinkList *list, void *data);    //O(n)

void *LinkListDelete(LinkList *list, int i);    //O(n)

bool LinkListSet(LinkList *list, int i, void *data);    //O(n)

void *LinkListGet(LinkList *list, int i);   //O(n)

bool LinkListMove(LinkList *list, int i);

bool LinkListEnd(LinkList *list);

void LinkListNext(LinkList *list);

void *LinkListCurrent(LinkList *list);

#define LinkListForEach(list) for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))

#define LinkListEntry(list, type) (type*)LinkListCurrent(list)

int LinkListFind(LinkList *list, void *data);

#ifdef __cplusplus
}
#endif

#endif
