#include "DualLinkList.h"
#include <stdio.h>

int main()
{
	DualLinkList* list = DualLinkListCreate();
	
	if(list != NULL)
	{	
		int i = 0;
		printf("此时双向链表长度为：%d\n", DualLinkListLength(list));
		
		printf("插入状态：%d\n", DualLinkListInsert(list, 0, 0));
		printf("插入状态：%d\n", DualLinkListInsert(list, 1, 1));
		printf("插入状态：%d\n", DualLinkListInsert(list, 2, 2));
		printf("插入状态：%d\n", DualLinkListInsert(list, 3, 3));
		printf("插入状态：%d\n", DualLinkListInsert(list, 9, 4));
		
		printf("此时双向链表长度为：%d\n", DualLinkListLength(list));
		
		printf("开始打印链表：\n");
		for(DualLinkListMove(list, 0); !DualLinkListEnd(list); DualLinkListNext(list), i++)
		{
			printf("data[%d] = %d\n", i, DualLinkListCurrent(list));
		}
		
		printf("开始打印链表：\n");
		i = 0;
		for(DualLinkListMove(list, DualLinkListLength(list) - 1); !DualLinkListEnd(list); DualLinkListPre(list), i++)
		{
			printf("data[%d] = %d\n", i, DualLinkListCurrent(list));
		}
		
		DualLinkListDelete(list, 0, NULL);	
		DualLinkListDelete(list, 0, NULL);
		
		printf("此时双向链表长度为：%d\n", DualLinkListLength(list));
		
		printf("删除状态：%d\n", DualLinkListDelete(list, 1, NULL)); 
		printf("此时双向链表长度为：%d\n", DualLinkListLength(list));
		
		list = DualLinkListDestroy(list);
	}

	return 0;
} 
