#include "LinkList.h"
#include <stdio.h>

int main()
{
	LinkList *list = LinkListCreate();
	
	if(list != NULL)
	{
		int i;
		
		printf("len = %d\n\n", LinkListLength(list));
		
		for(i = 0; i < 10; i++)
		{
			LinkListInsert(list, LinkListLength(list), i);
		}
		
		printf("len = %d\n\n", LinkListLength(list));
		
		for(i = 0; i < 5; i++)
		{
			LinkListDelete(list, 0, NULL);
		}
		
		printf("len = %d\n\n", LinkListLength(list));
		
		i = 0;
		printf("开始打印链表：\n");
		for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list), i++)
		{
			printf("list[%d] = %d\n", i, LinkListCurrent(list));
		}
		
		list = LinkListDestroy(list);
	}
	
	return 0;
}