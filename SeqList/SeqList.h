#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#define deBug() printf("File = %s\nLine = %d\n", __FILE__, __LINE__)

#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 100

#ifndef __cplusplus
	typedef int Bool;
	#define true 1
	#define false 0
#else
	typedef bool Bool;
#endif

#define MALLOC(type, size) 	(type*)malloc(sizeof(type) * size)
#define FREE(p)				(free(p), p = NULL)

typedef int DataType;

typedef struct
{
	DataType space[MAXSIZE];
	int size;
} SeqList;

SeqList* SeqListCreate(void);
SeqList* SeqListDestroy(SeqList *list);
int SeqListLength(SeqList *list);
int SeqListCapacity(SeqList *list);
Bool SeqListInsert(SeqList *list, int i, DataType data);
Bool SeqListDelete(SeqList *list, int i, DataType *data);
Bool SeqListSet(SeqList *list, int i, DataType data);
Bool SeqListGet(SeqList *list, int i, DataType *data);

#endif 
