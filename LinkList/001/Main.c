#include "LinkList.h"
#include <stdio.h>
#include <stdint.h>

int main()
{
    LinkList *list = LinkListCreate();

    if (list != NULL)
    {
        for (int i = 0; i < 10; i++)
        {
            int *data = MALLOC(int, 1);

            if (data == NULL)
            {
                printf("no momery to create int data: i = %d", i);
            }
            else
            {
                *data = i;
                bool ok = LinkListInsertBack(list, data);
                printf("result of inserting data: ok = %d", ok);
            }
        }

        LinkListForEach(list)
        {
            int *data = LinkListEntry(list, int);
            if (data != NULL)
            {
                printf("get data successful: data = %d", *data);
            }
            else
            {
                printf("get data failed.");
            }
        }

        int len = LinkListLength(list);

        for (int i = 0; i < len; i++)
        {
            int *data = (int *)(LinkListDelete(list, 0));

            if (data != NULL)
            {
                printf("get data successful: data = %d", *data);
                FREE(data);
            }
            else
            {
                printf("get data failed.");
            }
        }

        list = LinkListDestroy(list);
    }

    return 0;
}