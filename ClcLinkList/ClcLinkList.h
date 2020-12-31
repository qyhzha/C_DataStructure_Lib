#ifndef __LINKLIST_H__
#define __LINKLIST_H__

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

#define STRUCT(type) 	typedef struct _struct##type type;	\
						struct _struct##type

#define MALLOC(type, size) 	(type*)malloc(sizeof(type) * size)
#define FREE(p)				(free(p), p = NULL)

STRUCT(CLLNode)
{
	DataType data;
	CLLNode *next;
};

STRUCT(ClcLinkList)
{
	int len;
	CLLNode *next;
	CLLNode *m_current;
};

ClcLinkList* ClcLinkListCreate(void);
ClcLinkList* ClcLinkListDestroy(ClcLinkList *list);
int ClcLinkListLength(ClcLinkList *list);
Bool ClcLinkListInsert(ClcLinkList *list, int i, DataType data);
Bool ClcLinkListDelete(ClcLinkList *list, int i, DataType *data);
Bool ClcLinkListSet(ClcLinkList *list, int i, DataType data);
Bool ClcLinkListGet(ClcLinkList *list, int i, DataType *data);
CLLNode* ClcLinkListMove(ClcLinkList *list, int i);
Bool ClcLinkListEnd(ClcLinkList *list);
void ClcLinkListNext(ClcLinkList *list);
DataType ClcLinkListCurrent(ClcLinkList *list);
int ClcLinkListFind(ClcLinkList *list, DataType data);

#endif
