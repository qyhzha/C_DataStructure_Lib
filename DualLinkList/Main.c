#include "DualLinkList.h"
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
    DualLinkList *list = DualLinkListCreate();

    if (list != NULL)
    {
        int i = 0;
        printf("list length = %d\n", DualLinkListLength(list));

        for (i = 0; i < 10; i++)
        {
            int *data = MALLOC(int, 1);
            *data = i;
            DualLinkListInsertBack(list, data);
        }

        printf("list length = %d\n", DualLinkListLength(list));

        printf("begin printf:\n");
        int length = DualLinkListLength(list);
        for (i = 0; i < length; i++)
        {
            int *data = (int *)DualLinkListGet(list, i);

            printf("data[%d] = %d\n", i, *data);
        }
        printf("end printf\n");

        void *data = DualLinkListDelete(list, 0);
        FREE(data);

        printf("list length = %d\n", DualLinkListLength(list));

        printf("data = %d\n", *(int *)DualLinkListDelete(list, 1));
        printf("list length = %d\n", DualLinkListLength(list));

        list = DualLinkListDestroy(list);
    }

    return 0;
}
