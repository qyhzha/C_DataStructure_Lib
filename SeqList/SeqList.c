#include "SeqList.h"

SeqList* SeqListCreate(void)
{
	SeqList *ret = MALLOC(SeqList, 1);
	
	if(ret != NULL)	ret->size = 0;
	
	return ret;
}

SeqList* SeqListDestroy(SeqList *list)
{	
	return FREE(list);
}

int SeqListLength(SeqList *list)
{
	return (list != NULL) ? list->size : -1;
}

int SeqListCapacity(SeqList *list)
{
	return (list != NULL) ? MAXSIZE : -1;
}

Bool SeqListInsert(SeqList *list, int i, DataType data)
{  
	Bool ret = (list != NULL) && (i >= 0) && (i <= list->size) && (list->size < MAXSIZE);
	
	if(ret)
	{
		int j;
		
		for(j = list->size - 1; j >= i; j--)
		{
			list->space[j + 1] = list->space[j];
		}
		
		list->space[j] = data;
		
		list->size++;
	}
	
	return ret;
}

Bool SeqListDelete(SeqList *list, int i, DataType *data)
{
	Bool ret = (list != NULL) && (i >= 0) && (i < list->size);
	
	if(ret)
	{	
		if(data != NULL) *data = list->space[i];
		
		for(; i < list->size - 1; i++)
		{
			list->space[i] = list->space[i + 1]; 
		}
		
		list->size--;
	}
	
	return ret;
}

Bool SeqListSet(SeqList *list, int i, DataType data)
{
	return ((list != NULL) && (i >= 0) && (i < list->size)) ? (list->space[i] = data, true) : false;
}

Bool SeqListGet(SeqList *list, int i, DataType *data)
{	
	return ((list != NULL) && (i >= 0) && (i < list->size) && (data != 0)) ? (*data = list->space[i], true) : false;
}
