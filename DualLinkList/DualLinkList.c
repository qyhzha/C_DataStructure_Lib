#include "DualLinkList.h"
#include <stdio.h>
#include <stdlib.h>

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

typedef struct __DllNode
{
    void *data;
    struct __DllNode *pre;
    struct __DllNode *next;
} DllNode;

struct __DualLinkList
{
    DllNode *next;
    DllNode *m_current;
    int len;
};

static DllNode *move(DualLinkList *list, int i)
{
    if ((i >= 0) && (i < DualLinkListLength(list)))
    {
        DllNode *node = list->next;

        int j;
        for (j = 0; j < i; j++)
        {
            node = node->next;
        }

        return node;
    }

    return NULL;
}

DualLinkList *DualLinkListCreate(void)      //O(1)
{
    DualLinkList *list = MALLOC(DualLinkList, 1);

    if (list != NULL)
    {
        list->next = NULL;
        list->m_current = NULL;
        list->len = 0;
    }

    return list;
}

DualLinkList *DualLinkListDestroy(DualLinkList *list)   //O(n)
{
    if (list != NULL)
    {
        while (list->next != NULL)
        {
            void *data = DualLinkListDelete(list, 0);
            FREE(data);
        }

        FREE(list);
    }

    return NULL;
}

int DualLinkListLength(DualLinkList *list)  //O(1)
{
    return (list != NULL) ? list->len : -1;
}

bool DualLinkListInsert(DualLinkList *list, int i, void *data)       //O(n)
{
    bool ret = (i >= 0) && (i <= DualLinkListLength(list));

    if (ret)
    {
        DllNode *node = MALLOC(DllNode, 1);

        if (node)
        {
            node->data = data;

            if (0 == i)
            {
                node->next = list->next;
                node->pre = NULL;
                if (list->next != NULL) list->next->pre = node;
                list->next = node;
            }
            else
            {
                DllNode *pre = move(list, i - 1);

                node->next = pre->next;
                node->pre  = pre;

                if (pre->next != NULL) pre->next->pre = node;
                pre->next = node;
            }

            list->len++;
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

bool DualLinkListInsertBack(DualLinkList *list, void *data)
{
    return DualLinkListInsert(list, DualLinkListLength(list), data);
}

void *DualLinkListDelete(DualLinkList *list, int i)  //O(n)
{
    void *data = NULL;

    if ((i >= 0) && (i < DualLinkListLength(list)))
    {
        DllNode *node = list->next;

        if (0 == i)
        {
            data = node->data;

            list->next = node->next;
            if (node->next != NULL) node->next->pre = NULL;
        }
        else
        {
            DllNode *pre = move(list, i - 1);

            node = pre->next;

            data = node->data;

            pre->next = node->next;
            if (node->next != NULL) node->next->pre = pre;
        }

        FREE(node);

        list->len--;
    }

    return data;
}

bool DualLinkListSet(DualLinkList *list, int i, void *data)  //O(n)
{
    if (i >= 0 && i < DualLinkListLength(list))
    {
        DllNode *node = move(list, i);

        FREE(node->data);

        node->data = data;

        return true;
    }

    return false;
}

void *DualLinkListGet(DualLinkList *list, int i) //O(n)
{
    return ((i >= 0)
            && (i < DualLinkListLength(list))) ? move(list, i)->data : NULL;
}

//以下五个函数配合使用以遍历双向链表，时间复杂度为O(n)
bool DualLinkListMove(DualLinkList *list, int i)
{
    return ((i >= 0)
            && (i < DualLinkListLength(list))) ? (list->m_current = move(list, i),
                    true) : false;
}

bool DualLinkListEnd(DualLinkList *list)
{
    return (list != NULL) ? (list->m_current == NULL) : false;
}

void DualLinkListNext(DualLinkList *list)
{
    if ((list != NULL) && (list->m_current != NULL))
    {
        list->m_current = list->m_current->next;
    }
}

void DualLinkListPre(DualLinkList *list)
{
    if ((list != NULL) && (list->m_current != NULL))
    {
        list->m_current = list->m_current->pre;
    }
}

void *DualLinkListCurrent(DualLinkList *list)
{
    return ((list != NULL)
            && (list->m_current != NULL)) ? list->m_current->data : NULL;
}

int DualLinkListFind(DualLinkList *list, void *data) //O(n)
{
    int ret = -1;

    if (list)
    {
        int i = 0;

        for (DualLinkListMove(list, 0); !DualLinkListEnd(list);
             DualLinkListNext(list), i++)
        {
            if (DualLinkListCurrent(list) == data)
            {
                ret = i;
                break;
            }
        }
    }

    return ret;
}
