#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int main()
{
    LinkedList list = {NULL};

    {
        for (int i = 0; i < 5; i++)
        {
            int *data = (int *)malloc(sizeof(int));
            *data = i;

            if (linked_list_append(&list, data) != 0)
            {
                printf("Error\n");
                return 1;
            }
        }
        Node *node = list.head;
        while (node != NULL)
        {
            printf("%d\n", *(int *)node->data);
            node = node->next;
        }
        printf("===========================================================\n");
        for (Node *node = linked_list_pop(&list); node != NULL; node = linked_list_pop(&list))
        {
            printf("%d\n", *(int *)node->data);
            free(node->data);
            free(node);
        }
    }

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    {
        for (int i = 0; i < 5; i++)
        {
            int *data = (int *)malloc(sizeof(int));
            *data = i;

            if (linked_list_append(&list, data) != 0)
            {
                printf("Error\n");
                return 1;
            }
        }
        for (int i = 0; i < 5; i++)
        {
            Node *data = linked_list_remove(&list, 0);

            if (data == NULL)
            {
                printf("data == NULL\n");
                return 1;
            }

            printf("%d\n", *(int *)data->data);

            free(data->data);
            free(data);
        }
    }
    return 0;
}
