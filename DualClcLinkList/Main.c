#include "DualClcLinkList.h"
#include <stdio.h>

int main()
{
	DualClcLinkList *list = DualClcLinkListCreate();
	
	if(list != NULL)
	{
		int i, len = -1;
		
		for(i = 0; i < 10; i++)
		{
			DualClcLinkListInsert(list, 0, i);
		}
		
		len = DualClcLinkListLength(list);
		printf("链表长度为：%d\n\n", len);

		for(i = 0; i < len; i++)
		{
			int data = -1;
			DualClcLinkListGet(list, i, &data);
			printf("list[%d] = %d\n", i, data);
		}
		
		for(i = 0; i < 5; i++)
		{
			DualClcLinkListDelete(list, 0, NULL);
		}
		
		len = DualClcLinkListLength(list);
		printf("\n链表长度为：%d\n\n", len);
		
		for(i = 0; i < len; i++)
		{
			int data = -1;
			DualClcLinkListGet(list, i, &data);
			printf("list[%d] = %d\n", i, data);
		}
		
		printf("\n");
		
		list = DualClcLinkListDestroy(list);
	}
	
	return 0;
}