#include "SeqList.h"

int main() 
{
	SeqList* list = SeqListCreate();
	
	if(list != NULL)
	{
		printf("顺序表容量为：%d\n", SeqListCapacity(list));
		printf("顺序表长度为：%d\n", SeqListLength(list));
		
		printf("插入状态：%d\n", SeqListInsert(list, 0, 0));
		printf("插入状态：%d\n", SeqListInsert(list, 1, 1));
		printf("插入状态：%d\n", SeqListInsert(list, 2, 2));
		printf("插入状态：%d\n", SeqListInsert(list, 3, 3));
		printf("插入状态：%d\n", SeqListInsert(list, 9, 4));
		
		printf("此时顺序表长度为：%d\n", SeqListLength(list));
		
		SeqListDelete(list, 0, NULL);	
		SeqListDelete(list, 0, NULL);
		
		printf("此时顺序表长度为：%d\n", SeqListLength(list));
		
		printf("删除状态：%d\n", SeqListDelete(list, 1, NULL)); 
		printf("此时顺序表长度为：%d\n", SeqListLength(list));
		
		list = SeqListDestroy(list);	
	}
	
	return 0;
}
