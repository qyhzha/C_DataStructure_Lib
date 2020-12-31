#include "ClcLinkList.h"
#include <stdio.h>

int main()
{
	ClcLinkList* list = ClcLinkListCreate();
	
	if(list != NULL)
	{	
		int i = 0;
		printf("此时链表长度为：%d\n", ClcLinkListLength(list));
		
		printf("插入状态：%d\n", ClcLinkListInsert(list, 0, 0));
		printf("插入状态：%d\n", ClcLinkListInsert(list, 1, 1));
		printf("插入状态：%d\n", ClcLinkListInsert(list, 2, 2));
		printf("插入状态：%d\n", ClcLinkListInsert(list, 3, 3));
		printf("插入状态：%d\n", ClcLinkListInsert(list, 9, 4));
		
		printf("此时链表长度为：%d\n", ClcLinkListLength(list));
		
		printf("开始打印链表：\n");
		for(; i < ClcLinkListLength(list); i++)
		{
			int data;
			
			ClcLinkListGet(list, i, &data);
			
			printf("data[%d] = %d\n", i, data);
		}
		
		ClcLinkListDelete(list, 0, NULL);	
		ClcLinkListDelete(list, 0, NULL);
		
		printf("此时链表长度为：%d\n", ClcLinkListLength(list));
		
		printf("删除状态：%d\n", ClcLinkListDelete(list, 1, NULL)); 
		printf("此时链表长度为：%d\n", ClcLinkListLength(list));
		
		list = ClcLinkListDestroy(list);
	}

	return 0;
} 
