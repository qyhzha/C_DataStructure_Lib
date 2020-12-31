#include "LinkList.h"
#include <stdlib.h>
#include <stdio.h>

#define deBug(fmt, ...) printf("[%s, %d]"fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#define MALLOC(type, size)  (type*)malloc(sizeof(type) * size)
#define FREE(p)             (free(p), p = NULL)

#define STRUCT(type)    typedef struct __struct##type type;\
                        struct __struct##type

STRUCT(LLNode)
{
    DataType data;
    LLNode *next;
};

struct __LinkList
{
    int len;
    LLNode *next;
    LLNode *m_current;
};

LLNode *move(LinkList *list, int i)
{
    LLNode *ret = NULL;

    list->m_current = NULL;

    if ((list != NULL) && (i >= 0) && (i < LinkListLength(list)))
    {
        LLNode *node = list->next;

        if (node != NULL)
        {
            int j;

            for (j = 0; j < i; j++)
            {
                node = node->next;
            }

            ret = node;
            list->m_current = node;
        }
    }

    return ret;
}

LinkList *LinkListCreate(void)      //O(1)
{
    LinkList *list = MALLOC(LinkList, 1);

    if (list != NULL)
    {
        list->len = 0;
        list->next = NULL;
        list->m_current = NULL;
    }

    return list;
}

LinkList *LinkListDestroy(LinkList *list)   //O(n)
{
    if (list != NULL)
    {
        while (list->next != NULL)
        {
            LinkListDelete(list, 0, NULL);
        }

        FREE(list);
    }

    return NULL;
}

int LinkListLength(LinkList *list)  //O(1)
{
    return (list != NULL) ? list->len : -1;
}

bool LinkListInsert(LinkList *list, int i, DataType data)       //O(n)
{
    bool ret = (list != NULL) && (i >= 0) && (i <= LinkListLength(list));

    if (ret)
    {
        LLNode *node = MALLOC(LLNode, 1);

        if (node != NULL)
        {
            if (0 == i)
            {
                node->data = data;
                node->next = list->next;

                list->next = node;
            }
            else
            {
                LLNode *pre = move(list, i - 1);

                node->data = data;
                node->next = pre->next;

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

bool LinkListDelete(LinkList *list, int i, DataType *data)  //O(n)
{
    bool ret = (i >= 0) && (i < LinkListLength(list));

    if (ret)
    {
        LLNode *node = list->next;

        if (0 == i)
        {
            if (data) *data = node->data;
            list->next = node->next;
        }
        else
        {
            LLNode *pre = move(list, i - 1);

            node = pre->next;

            if (data) *data = node->data;

            pre->next = node->next;
        }

        free(node);
        list->len--;
    }

    return ret;
}

bool LinkListSet(LinkList *list, int i, DataType data)  //O(n)
{
    return ((i >= 0)
            && (i < LinkListLength(list))) ? (move(list, i)->data = data,
                    true) : false;
}

bool LinkListGet(LinkList *list, int i, DataType *data) //O(n)
{
    return ((data != NULL) && (i >= 0)
            && (i < LinkListLength(list))) ? (*data = move(list, i)->data,
                    true) : false;
}

//下面四个配合使用用于遍历链表，时间复杂度为O(n)
bool LinkListMove(LinkList *list, int i)
{
    return ((i >= 0)
            && (i < LinkListLength(list))) ? (list->m_current = move(list, i),
                    true) : false;
}

bool LinkListEnd(LinkList *list)
{
    return (list != NULL) ? (list->m_current == NULL) : false;
}

void LinkListNext(LinkList *list)
{
    if ((list != NULL) && (list->m_current != NULL))
    {
        list->m_current = list->m_current->next;
    }
}

DataType LinkListCurrent(LinkList *list)
{
    return ((list != NULL)
            && (list->m_current != NULL)) ? list->m_current->data : (DataType)0;
}

int LinkListFind(LinkList *list, DataType data) //O(n)
{
    int ret = -1;

    if (list)
    {
        int i = 0;

        for (move(list, 0); !LinkListEnd(list); LinkListNext(list), i++)
        {
            if (LinkListCurrent(list) == data)
            {
                ret = i;
                break;
            }
        }
    }

    return ret;
}
