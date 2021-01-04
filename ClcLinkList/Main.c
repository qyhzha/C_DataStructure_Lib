#include "ClcLinkList.h"
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(type, size)  (printf("malloc\n"), (type*)malloc(sizeof(type) * size))
#define FREE(p)             \
do                          \
{                           \
    if(p != NULL)           \
    {                       \
        free(p);            \
        printf("free\n");   \
        p = NULL;           \
    }                       \
}while(0)

int main()
{
    ClcLinkList *list = ClcLinkListCreate();

    if (list != NULL)
    {
        int i = 0;
        printf("list length = %d\n", ClcLinkListLength(list));

        for (i = 0; i < 10; i++)
        {
            int *data = MALLOC(int, 1);
            *data = i;
            ClcLinkListInsert(list, i * 3, data);
        }

        printf("list length = %d\n", ClcLinkListLength(list));

        printf("begin printf:\n");
        int length = ClcLinkListLength(list);
        for (i = 0; i < length; i++)
        {
            int *data = (int *)ClcLinkListGet(list, i);

            printf("data[%d] = %d\n", i, *data);
        }
        printf("end printf\n");

        void *data = ClcLinkListDelete(list, 0);
        FREE(data);

        printf("list length = %d\n", ClcLinkListLength(list));

        printf("data = %d\n", *(int *)ClcLinkListDelete(list, 1));
        printf("list length = %d\n", ClcLinkListLength(list));

        list = ClcLinkListDestroy(list);
    }

    return 0;
}
