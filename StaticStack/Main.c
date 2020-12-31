#include "StaticStack.h"
#include <stdio.h>

int main()
{
	StaticStack* stack = StaticStackCreate();
	
	if(stack != NULL)
	{
		int i, len = -1, data = -1;
		
		for(i = 0; i < StaticStackCapacity(stack); i++)
		{
			StaticStackPush(stack, i);
		}
		
		printf("����״̬��%d\n", StaticStackPush(stack, 100));
		
		len = StaticStackLength(stack);
		printf("len = %d\n\n", len);
		
		for(i = 0; i < len / 2; i++)
		{
			StaticStackPop(stack, NULL);
		}
		
		len = StaticStackLength(stack);
		printf("len = %d\n\n", len);
		
		printf("��ӡջ�����ݣ�\n");
		for(i = 0; i < len; i++)
		{
			StaticStackPop(stack, &data);
			printf("data[%02d] = %-2d\n", i, data);
		}
		
		stack = StaticStackDestroy(stack);
	}
	
	return 0;
}