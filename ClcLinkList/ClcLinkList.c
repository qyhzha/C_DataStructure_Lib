#include "ClcLinkList.h"
#include <stdlib.h>
#include <stdio.h>

#define deBug(fmt, ...) printf("[%s, %d]"fmt, __FILE__, __LINE__, ##__VA_ARGS__)

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

typedef struct __ClcNode
{
    void *data;
    struct __ClcNode *next;
} ClcNode;

struct __ClcLinkList
{
    int len;
    ClcNode *next;
    ClcNode *m_current;
};

static ClcNode *move(ClcLinkList *list, int i)
{
    int length = ClcLinkListLength(list);

    i = (length > 0 && i >= 0) ? i % length : -1;

    if (i >= 0)
    {
        ClcNode *node = list->next;

        int j;
        for (j = 0; j < i; j++)
        {
            node = node->next;
        }

        return node;
    }

    return NULL;
}

ClcLinkList *ClcLinkListCreate(void)    //O(1)
{
    ClcLinkList *list = MALLOC(ClcLinkList, 1);

    if (list != NULL)
    {
        list->next = NULL;
        list->m_current = NULL;
        list->len = 0;
    }

    return list;
}

ClcLinkList *ClcLinkListDestroy(ClcLinkList *list)      //o(n)
{
    if (list != NULL)
    {
        ClcNode *node = list->next;

        if (node != NULL)
        {
            ClcNode *pre = NULL;

            do
            {
                pre = node;
                node = node->next;
                FREE(pre->data);
                FREE(pre);
            } while ((node != NULL) && (node != list->next));
        }

        FREE(list);
    }

    return NULL;
}

int ClcLinkListLength(ClcLinkList *list)    //O(1)
{
    return (list != NULL) ? list->len : -1;
}

bool ClcLinkListInsert(ClcLinkList *list, int i, void *data)     //O(n)
{
    i = (ClcLinkListLength(list) == 0) ? 0 : i;
    if (list != NULL && i >= 0)
    {
        ClcNode *node = MALLOC(ClcNode, 1);

        if (node != NULL)
        {
            if (0 == i)
            {
                node->data = data;

                if (list->next != NULL)
                {
                    move(list, ClcLinkListLength(list) - 1)->next = node;
                    node->next = list->next;
                }
                else
                {
                    node->next = node;
                }

                list->next = node;
            }
            else
            {
                ClcNode *pre = move(list, i - 1);

                node->data = data;

                node->next = pre->next;
                pre->next = node;
            }

            list->len++;

            return true;
        }
    }

    return false;
}

bool ClcLinkListInsertBack(ClcLinkList *list, void *data)
{
    return ClcLinkListInsert(list, ClcLinkListLength(list), data);
}

void *ClcLinkListDelete(ClcLinkList *list, int i)    //O(n)
{
    void *data = NULL;

    if (i >= 0 && ClcLinkListLength(list) > 0)
    {
        ClcNode *node = NULL;

        if (0 == i)
        {
            node = list->next;

            if (node->next == node) list->next = NULL;
            else
            {
                move(list, ClcLinkListLength(list) - 1)->next = node->next;
                list->next = node->next;
            }
        }
        else
        {
            ClcNode *pre = move(list, i - 1);

            node = pre->next;

            pre->next = node->next;
        }

        data = node->data;

        FREE(node);

        list->len--;
    }

    return data;
}

bool ClcLinkListSet(ClcLinkList *list, int i, void *data)    //O(n)
{
    if (i >= 0 && ClcLinkListLength(list) > 0)
    {
        ClcNode *node = move(list, i);
        FREE(node->data);
        node->data = data;
        return true;
    }

    return false;
}

void *ClcLinkListGet(ClcLinkList *list, int i)   //O(n)
{
    return ((ClcLinkListLength(list) > 0) && (i >= 0)) ? move(list, i)->data : NULL;
}

//下面4个函数配合使用以完成循环链表的遍历，时间复杂度为O(n)
bool ClcLinkListMove(ClcLinkList *list, int i)
{
    return (i >= 0
            && ClcLinkListLength(list) > 0) ? (list->m_current = move(list, i),
                    true) : false;
}

bool ClcLinkListEnd(ClcLinkList *list)
{
    return (list != NULL) ? (list->m_current == NULL) : false;
}

void ClcLinkListNext(ClcLinkList *list)
{
    if ((list != NULL) && (list->m_current != NULL))
    {
        list->m_current = list->m_current->next;
    }
}

void *ClcLinkListCurrent(ClcLinkList *list)
{
    return ((list != NULL)
            && (list->m_current != NULL)) ? list->m_current->data : NULL;
}

int ClcLinkListFind(ClcLinkList *list, void *data)   //O(n)
{
    int ret = -1;

    if (list)
    {
        ClcNode *node = list->next;

        if (node != NULL)
        {
            int i = 0;
            do
            {
                if (node->data == data)
                {
                    ret = i;
                    break;
                }

                node = node->next;
            } while (node != list->next);
        }
    }

    return ret;
}
