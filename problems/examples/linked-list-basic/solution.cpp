#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
};
void add(Node **phead, int munber);

int main()
{
    Node *head = NULL;
    int number;
    int i = 0;
    do
    {
        scanf("%d", &number);
        if (number != -1)
        {
            add(&head, number);
        }
    } while (number != -1);

    for (Node *q = head; q != NULL; q = q->next)
    {
        i += q->value;
    }

    printf("%d", i);

    return 0;
}

void add(Node **phead, int number)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = number;
    new_node->next = NULL;
    if (*phead != NULL)
    {
        Node *last = *phead;
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = new_node;
    }
    else
    {
        *phead = new_node;
    }

    return;
}
