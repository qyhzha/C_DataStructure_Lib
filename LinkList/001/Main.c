#include "LinkList.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    LinkList *list = LinkListCreate();

    if (list != NULL)
    {
        for (int i = 0; i < 10; i++)
        {
            int *data = (int*)malloc(sizeof(4));

            if (data == NULL)
            {
                printf("no momery to create int data: i = %d\n", i);
            }
            else
            {
                *data = i;
                bool ok = LinkListInsertBack(list, data);
                printf("result of inserting data: ok = %d\n", ok);
            }
        }

        LinkListForEach(list)
        {
            int *data = LinkListEntry(list, int);
            if (data != NULL)
            {
                printf("get data successful: data = %d\n", *data);
            }
            else
            {
                printf("get data failed.\n");
            }
        }

        int len = LinkListLength(list);

        for (int i = 0; i < len; i++)
        {
            int *data = (int *)(LinkListDelete(list, 0));

            if (data != NULL)
            {
                printf("get data successful: data = %d\n", *data);
                free(data);
            }
            else
            {
                printf("get data failed.\n");
            }
        }

        list = LinkListDestroy(list);
    }

    return 0;
}