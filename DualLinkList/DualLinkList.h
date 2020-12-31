#ifndef __DUALLINKLIST_H__
#define __DUALLINKLIST_H__

typedef int DataType; 

#define deBug() printf("File = %s\nLine = %d\n", __FILE__, __LINE__)

#include <stdio.h>
#include <stdlib.h>

#ifndef __cplusplus
	typedef int Bool;
	#define true 1
	#define false 0
#else
	typedef bool Bool;
#endif

#define STRUCT(type) 	typedef struct _struct##type type;	\
						struct _struct##type

#define MALLOC(type, size) 	(type*)malloc(sizeof(type) * size)
#define FREE(p)				(free(p), p = NULL)

STRUCT(DLLNode)
{
	DataType data;
	DLLNode *pre;
	DLLNode *next;
};

STRUCT(DualLinkList)
{
	DLLNode *next;
	DLLNode *m_current;
	int len;
};

DualLinkList* DualLinkListCreate(void);
DualLinkList* DualLinkListDestroy(DualLinkList *list);
int DualLinkListLength(DualLinkList *list);
Bool DualLinkListInsert(DualLinkList *list, int i, DataType data);
Bool DualLinkListDelete(DualLinkList *list, int i, DataType *data);
int DualLinkListFind(DualLinkList *list, DataType data); 
Bool DualLinkListSet(DualLinkList *list, int i, DataType data);
Bool DualLinkListGet(DualLinkList *list, int i, DataType *data);
DLLNode* DualLinkListMove(DualLinkList *list, int i);
Bool DualLinkListEnd(DualLinkList *list);
void DualLinkListNext(DualLinkList *list);
void DualLinkListPre(DualLinkList *list);
DataType DualLinkListCurrent(DualLinkList *list);

#endif
