#include "LinkList.h"
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(type, size)  ((type*)malloc(sizeof(type) * size))
#define FREE(p)             (free(p), p = NULL)

typedef struct __Node
{
    void *data;
    struct __Node *next;
} Node;

struct __LinkList
{
    int len;
    Node *next;
    Node *m_current;
};

static Node *move(LinkList *list, int i)
{
    if ((i >= 0) && (i < LinkListLength(list)))
    {
        Node *node = list->next;

        int j;
        for (j = 0; j < i; j++)
        {
            node = node->next;
        }

        return node;
    }

    return NULL;
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
            LinkListDelete(list, 0);
        }

        FREE(list);
    }

    return NULL;
}

int LinkListLength(LinkList *list)  //O(1)
{
    return (list != NULL) ? list->len : -1;
}

bool LinkListInsert(LinkList *list, int i, void *data)      //O(n)
{
    bool ret = (i >= 0) && (i <= LinkListLength(list));

    if (ret)
    {
        Node *node = MALLOC(Node, 1);

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
                Node *pre = move(list, i - 1);

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

bool LinkListInsertBack(LinkList *list, void *data)
{
    return LinkListInsert(list, LinkListLength(list), data);
}

void *LinkListDelete(LinkList *list, int i) //O(n)
{
    void *ret = NULL;

    if ((i >= 0) && (i < LinkListLength(list)))
    {
        Node *node = list->next;

        if (0 == i)
        {
            list->next = node->next;
        }
        else
        {
            Node *pre = move(list, i - 1);

            node = pre->next;

            pre->next = node->next;
        }

        ret = node->data;

        FREE(node);
        list->len--;
    }

    return ret;
}

void *LinkListDeleteBack(LinkList *list)
{
    return LinkListDelete(list, LinkListLength(list) - 1);
}

bool LinkListSet(LinkList *list, int i, void *data) //O(n)
{
    return ((i >= 0)
            && (i < LinkListLength(list))) ? (move(list, i)->data = data, true) : false;
}

void *LinkListGet(LinkList *list, int i)    //O(n)
{
    return ((i >= 0) && (i < LinkListLength(list))) ? (move(list, i)->data) : NULL;
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

void *LinkListCurrent(LinkList *list)
{
    return ((list != NULL)
            && (list->m_current != NULL)) ? list->m_current->data : NULL;
}

int LinkListFind(LinkList *list, void *data)    //O(n)
{
    int ret = -1;

    if (list != NULL && NULL != data)
    {
        int i = 0;

        for (LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list), i++)
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