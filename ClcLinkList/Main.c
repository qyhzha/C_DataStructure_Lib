#include "ClcLinkList.h"
#include <stdio.h>

int main()
{
	ClcLinkList* list = ClcLinkListCreate();
	
	if(list != NULL)
	{	
		int i = 0;
		printf("��ʱ������Ϊ��%d\n", ClcLinkListLength(list));
		
		printf("����״̬��%d\n", ClcLinkListInsert(list, 0, 0));
		printf("����״̬��%d\n", ClcLinkListInsert(list, 1, 1));
		printf("����״̬��%d\n", ClcLinkListInsert(list, 2, 2));
		printf("����״̬��%d\n", ClcLinkListInsert(list, 3, 3));
		printf("����״̬��%d\n", ClcLinkListInsert(list, 9, 4));
		
		printf("��ʱ������Ϊ��%d\n", ClcLinkListLength(list));
		
		printf("��ʼ��ӡ����\n");
		for(; i < ClcLinkListLength(list); i++)
		{
			int data;
			
			ClcLinkListGet(list, i, &data);
			
			printf("data[%d] = %d\n", i, data);
		}
		
		ClcLinkListDelete(list, 0, NULL);	
		ClcLinkListDelete(list, 0, NULL);
		
		printf("��ʱ������Ϊ��%d\n", ClcLinkListLength(list));
		
		printf("ɾ��״̬��%d\n", ClcLinkListDelete(list, 1, NULL)); 
		printf("��ʱ������Ϊ��%d\n", ClcLinkListLength(list));
		
		list = ClcLinkListDestroy(list);
	}

	return 0;
} 
