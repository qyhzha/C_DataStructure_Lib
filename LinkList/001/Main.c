#include "LinkList.h"
#include <stdio.h>
#include <string.h>

typedef struct
{
	char name[10];
	int age;
	int score;
} student;

int main()
{
	LinkList *list = LinkListCreate();
	
	if(list != NULL)
	{
		int i;
		
		printf("len = %d\n\n", LinkListLength(list));
		
		for(i = 0; i < 10; i++)
		{
			student *qin = MALLOC(student, 1);
			strcpy(qin->name, "qin");
			qin->age = i;
			qin->score = i * 10;
			LinkListInsert(list, LinkListLength(list), qin);
		}
		
		printf("len = %d\n\n", LinkListLength(list));
		
		for(i = 0; i < 5; i++)
		{
			LinkListDelete(list, 0);
		}
		
		printf("len = %d\n\n", LinkListLength(list));
		
		i = 0;
		printf("开始打印链表：\n");
		for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list), i++)
		{
			//printf("list[%d] = %hd\n", i, *((short*)LinkListCurrent(list)));
			student *data = LinkListCurrent(list, student);
			printf("list[%d]->name  = %s\n", i, data->name);
			printf("list[%d]->age   = %d\n", i, data->age);
			printf("list[%d]->score = %d\n\n", i, data->score);
		}
		
		list = LinkListDestroy(list);
	}
	
	return 0;
}