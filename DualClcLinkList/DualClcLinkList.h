#ifndef __DUALCLCLINKLIST_H__
#define __DUALCLCLINKLIST_H__

typedef int DataType;

#define deBug() printf("File = %s\nLine = %d\n", __FILE__, __LINE__)

#include <stdlib.h>
#include <stdio.h>

#ifndef __cplusplus
	typedef int Bool;
	#define true 1
	#define false 0
#else
	typedef bool Bool;
#endif

#define MALLOC(type, size) 	(type*)malloc(sizeof(type) * size)
#define FREE(p)				(free(p), p = NULL)

#define STRUCT(type)	typedef struct _struct##type type;\
						struct _struct##type 

STRUCT(DCLLNode)
{
	DataType data;
	DCLLNode *pre;
	DCLLNode *next;
};

STRUCT(DualClcLinkList)
{
	int len;
	DCLLNode *next;
	DCLLNode *m_current;
};

DualClcLinkList* DualClcLinkListCreate(void);
DualClcLinkList* DualClcLinkListDestroy(DualClcLinkList *list);
int DualClcLinkListLength(DualClcLinkList *list);
Bool DualClcLinkListInsert(DualClcLinkList *list, int i, DataType data);
Bool DualClcLinkListDelete(DualClcLinkList *list, int i, DataType *data);
Bool DualClcLinkListSet(DualClcLinkList *list, int i, DataType data);
Bool DualClcLinkListGet(DualClcLinkList *list, int i, DataType *data);
DCLLNode* DualClcLinkListMove(DualClcLinkList *list, int i);
Bool DualClcLinkListEnd(DualClcLinkList *list);
void DualClcLinkListNext(DualClcLinkList *list);
void DualClcLinkListPre(DualClcLinkList *list);
DataType DualClcLinkListCurrent(DualClcLinkList *list);
int DualClcLinkListFind(DualClcLinkList *list, DataType data);

#endif
