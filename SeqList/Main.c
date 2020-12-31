#include "SeqList.h"

int main() 
{
	SeqList* list = SeqListCreate();
	
	if(list != NULL)
	{
		printf("˳�������Ϊ��%d\n", SeqListCapacity(list));
		printf("˳�����Ϊ��%d\n", SeqListLength(list));
		
		printf("����״̬��%d\n", SeqListInsert(list, 0, 0));
		printf("����״̬��%d\n", SeqListInsert(list, 1, 1));
		printf("����״̬��%d\n", SeqListInsert(list, 2, 2));
		printf("����״̬��%d\n", SeqListInsert(list, 3, 3));
		printf("����״̬��%d\n", SeqListInsert(list, 9, 4));
		
		printf("��ʱ˳�����Ϊ��%d\n", SeqListLength(list));
		
		SeqListDelete(list, 0, NULL);	
		SeqListDelete(list, 0, NULL);
		
		printf("��ʱ˳�����Ϊ��%d\n", SeqListLength(list));
		
		printf("ɾ��״̬��%d\n", SeqListDelete(list, 1, NULL)); 
		printf("��ʱ˳�����Ϊ��%d\n", SeqListLength(list));
		
		list = SeqListDestroy(list);	
	}
	
	return 0;
}
