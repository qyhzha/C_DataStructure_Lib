#include "DynamicStack.h"
#include <stdio.h>

int main()
{
	DynamicStack* stack = DynamicStackCreate();
	
	if(stack != NULL)
	{
		int i, len = -1;
		
		for(i = 0; i < 10; i++)
		{
			DynamicStackPush(stack, i);
		}
		
		len = DynamicStackLength(stack);
		printf("��ʱջ�ĳ���Ϊ��%d\n\n", len);
		
		for(i = 0; i < 5; i++)
		{
			DynamicStackPop(stack, NULL);
		}
		
		len = DynamicStackLength(stack);
		printf("��ʱջ�ĳ���Ϊ��%d\n\n", len);
		
		printf("��ʼ��ӡջ��Ԫ�أ�\n");
		for(i = 0; i < len; i++)
		{
			int data;
			
			DynamicStackPop(stack, &data);
			
			printf("stack[%05d] = %-5d\n", i, data);
		}
	
		DynamicStackDestroy(stack);
	}
	
	return 0;
}