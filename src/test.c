#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LinkedList.h"

#define TEST_SIZE 300

void test_append(void)
{
    printf("Testing append\n");
    LinkedList list = {NULL};

    for (int i = 0; i < TEST_SIZE; i++)
    {
        int *data = (int *)malloc(sizeof(int));
        assert(data != NULL);
        *data = i;

        int ret = linked_list_append(&list, data);
        assert(ret == 0);
    }

    {
        Node *node = list.head;
        for (int i = 0; i < TEST_SIZE; i++)
        {
            assert(node != NULL);
            assert(node->data != NULL);

            Node *tmp = node;
            assert(*(int *)node->data == i);
            node = node->next;

            free(tmp->data);
            free(tmp);
        }
        assert(node == NULL);
    }
}

void test_pop(void)
{
    printf("Testing pop\n");
    LinkedList list = {NULL};

    for (int i = 0; i < TEST_SIZE; i++)
    {
        int *data = (int *)malloc(sizeof(int));
        assert(data != NULL);
        *data = i;

        int ret = linked_list_append(&list, data);
        assert(ret == 0);
    }

    {
        int count = TEST_SIZE;

        for (Node *node = linked_list_pop(&list); node != NULL; node = linked_list_pop(&list))
        {
            assert(*(int *)node->data == --count);

            free(node->data);
            free(node);
        }
        assert(count == 0);
    }
}

void test_insert(void)
{
    printf("Testing insert\n");
    LinkedList list = {NULL};

    {
        int *data = (int *)malloc(sizeof(int));
        assert(data != NULL);
        *data = 0;

        int ret = linked_list_append(&list, data);
        assert(ret == 0);
    }

    {
        int *data = (int *)malloc(sizeof(int));
        assert(data != NULL);
        *data = 1;

        int ret = linked_list_append(&list, data);
        assert(ret == 0);
    }

    for (int i = 2; i < TEST_SIZE; i++)
    {
        int *data = (int *)malloc(sizeof(int));
        assert(data != NULL);
        *data = i;

        int ret = linked_list_add(&list, data, 1);
        assert(ret == 0);
    }

    {
        Node *node = list.head;
        assert(node != NULL);
        assert(*(int *)node->data == 0);

        node = node->next;
        assert(node != NULL);
        for (int i = TEST_SIZE - 1; i > 0; i--)
        {
            assert(node != NULL);
            assert(*(int *)node->data == i);
            node = node->next;
        }
        assert(node == NULL);
    }

    {
        Node *node = list.head;
        while (node != NULL)
        {
            Node *tmp = node;
            node = node->next;

            free(tmp->data);
            free(tmp);
        }
    }
}

void test_remove(void)
{
    printf("Testing remove\n");
    LinkedList list = {NULL};

    for (int i = 0; i < TEST_SIZE; i++)
    {
        int *data = (int *)malloc(sizeof(int));
        assert(data != NULL);
        *data = i;

        int ret = linked_list_append(&list, data);
        assert(ret == 0);
    }

    for (int i = 0; i < TEST_SIZE; i++)
    {
        Node *data = linked_list_remove(&list, 0);

        assert(data != NULL);
        assert(*(int *)data->data == i);

        free(data->data);
        free(data);
    }
}

int main(void)
{
    test_append();
    test_pop();
    test_insert();
    test_remove();
    return 0;
}
