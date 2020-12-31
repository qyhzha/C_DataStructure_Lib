#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef int DataType;

#define deBug() printf("File = %s\nLine = %d\n", __FILE__, __LINE__)

#include <stdlib.h>

#ifndef __cplusplus
	typedef int Bool;
	#define true 1
	#define false 0
#else
	typedef bool Bool;
#endif

#define MALLOC(type, size)	(type*)malloc(sizeof(type) * size)
#define FREE(p)				(free(p), p = NULL)

#define STRUCT(type) 	typedef struct __struct##type type;\
						struct __struct##type 

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
