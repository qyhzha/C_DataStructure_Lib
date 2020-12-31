#include "DualLinkList.h"
#include <stdio.h>

int main()
{
	DualLinkList* list = DualLinkListCreate();
	
	if(list != NULL)
	{	
		int i = 0;
		printf("��ʱ˫��������Ϊ��%d\n", DualLinkListLength(list));
		
		printf("����״̬��%d\n", DualLinkListInsert(list, 0, 0));
		printf("����״̬��%d\n", DualLinkListInsert(list, 1, 1));
		printf("����״̬��%d\n", DualLinkListInsert(list, 2, 2));
		printf("����״̬��%d\n", DualLinkListInsert(list, 3, 3));
		printf("����״̬��%d\n", DualLinkListInsert(list, 9, 4));
		
		printf("��ʱ˫��������Ϊ��%d\n", DualLinkListLength(list));
		
		printf("��ʼ��ӡ����\n");
		for(DualLinkListMove(list, 0); !DualLinkListEnd(list); DualLinkListNext(list), i++)
		{
			printf("data[%d] = %d\n", i, DualLinkListCurrent(list));
		}
		
		printf("��ʼ��ӡ����\n");
		i = 0;
		for(DualLinkListMove(list, DualLinkListLength(list) - 1); !DualLinkListEnd(list); DualLinkListPre(list), i++)
		{
			printf("data[%d] = %d\n", i, DualLinkListCurrent(list));
		}
		
		DualLinkListDelete(list, 0, NULL);	
		DualLinkListDelete(list, 0, NULL);
		
		printf("��ʱ˫��������Ϊ��%d\n", DualLinkListLength(list));
		
		printf("ɾ��״̬��%d\n", DualLinkListDelete(list, 1, NULL)); 
		printf("��ʱ˫��������Ϊ��%d\n", DualLinkListLength(list));
		
		list = DualLinkListDestroy(list);
	}

	return 0;
} 
