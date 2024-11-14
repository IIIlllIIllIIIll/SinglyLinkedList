#include <stdlib.h>
#include "LinkedList.h"

int linked_list_add(LinkedList *list, void *data, int location)
{
    if (list == NULL)
    {
        return -1;
    }
    else if (location < -1)
    {
        return -1;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        return -1;
    }
    node->next = NULL;
    node->data = data;

    Node *li = (Node *)list;
    if (location == -1)
    {
        while (li->next != NULL)
        {
            li = li->next;
        }
        li->next = node;
    }
    else
    {
        for (int i = 0; i < location; i++)
        {
            if (li->next == NULL)
            {
                return 1;
            }
            li = li->next;
        }
        node->next = li->next;
        li->next = node;
    }
    return 0;
}
int linked_list_append(LinkedList *list, void *data)
{
    return linked_list_add(list, data, -1);
}

Node *linked_list_remove(LinkedList *list, int location)
{
    if (list->head == NULL)
    {
        return NULL;
    }
    else if (location < -1)
    {
        return NULL;
    }

    Node *li = (Node *)list;
    if (location == -1)
    {
        while (li->next->next != NULL)
        {
            li = li->next;
        }
        Node *node = li->next;
        li->next = NULL;
        return node;
    }
    else
    {
        for (int i = 0; i < location; i++)
        {
            if (li->next == NULL)
            {
                return NULL;
            }
            li = li->next;
        }
        Node *node = li->next;
        li->next = node->next;
        return node;
    }
}

Node *linked_list_pop(LinkedList *list)
{
    return linked_list_remove(list, -1);
}