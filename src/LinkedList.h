#pragma once

typedef struct Node
{
    struct Node *next;
    void *data;
} Node;

typedef struct LinkedList
{
    Node *head;
} LinkedList;

int linked_list_add(LinkedList *list, void *data, int location);
int linked_list_append(LinkedList *list, void *data);

Node *linked_list_remove(LinkedList *list, int location);
Node *linked_list_pop(LinkedList *list);
