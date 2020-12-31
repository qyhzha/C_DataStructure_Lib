#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdio.h>
#include <stdlib.h>

#define deBug() printf("File = %s\nLine = %d\n", __FILE__, __LINE__)

#ifndef __cplusplus
typedef enum {false, true} bool;
#endif

#define MALLOC(type, size)  ((type*)malloc(sizeof(type) * size))
#define FREE(p)             (free(p), p = NULL)

#define STRUCT(type)    typedef struct __struct##type type;\
                        struct __struct##type

#define LinkListCurrent(list, type) (type*)current(list)

typedef struct __LinkList LinkList;

LinkList *LinkListCreate(void);
LinkList *LinkListDestroy(LinkList *list);
int LinkListLength(LinkList *list);
bool LinkListInsert(LinkList *list, int i, void *data);
bool LinkListDelete(LinkList *list, int i);
int LinkListFind(LinkList *list, void *data);
bool LinkListSet(LinkList *list, int i, void *data);
void *LinkListGet(LinkList *list, int i);
bool LinkListMove(LinkList *list, int i);
bool LinkListEnd(LinkList *list);
void LinkListNext(LinkList *list);
//void *LinkListCurrent(LinkList *list);
void *current(LinkList *list);

#endif
