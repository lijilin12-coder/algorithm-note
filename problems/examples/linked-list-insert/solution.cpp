#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main()
{
    Node *head;
    head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    head->value = 0;
    int number = 0;
    int i = 0;
    Node *new_node;
    do
    {
        scanf("%d", &number);
        new_node = (Node *)malloc(sizeof(Node));
        new_node->next = NULL;
        new_node->value = number;
        i++;
        Node *last;
        last = head;
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = new_node;
    } while (number != -1);
    int pos, value;
    scanf("%d %d", &pos, &value);
    Node *p;
    Node *q;
    p = head;
    q = head->next;
    new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    if (pos > 0 && pos < i + 1)
    {
        int m = 0;
        Node *n;
        n = new_node;
        while (m < i + 1)
        {
            m++;
            if (m == pos)
            {
                p->next = n;
                n->next = q;
                break;
            }
            else
            {
                p = q;
                q = q->next;
            }
        }
    }
    for (Node *m = head->next; m->next != NULL; m = m->next)
    {
        printf("%d ", m->value);
    }
    printf("\n");

    return 0;
}
