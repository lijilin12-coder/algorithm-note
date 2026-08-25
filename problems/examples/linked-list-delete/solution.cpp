#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main()
{
    Node *head = list_create();
    /* Node *new_node = (Node *)malloc(sizeof(Node));
     head = new_node;
     head->value = 0;
     head->next = nullptr;*/
    int number = 0;
    do
    {
        scanf("%d", &number);
        list_push_back(head, number);

        /* Node *new_node = (Node *)malloc(sizeof(Node));
         new_node->next = nullptr;
         new_node->value = number;
         Node *last;
         last = head;
         while (last->next != nullptr)
         {
             last = last->next;
         }
         last->next = new_node;*/
    } while (number != -1);
    int value;
    scanf("%d", &value);
    Node *p = head;
    Node *q = head->next;
    while (q->value != -1 && q != nullptr)
    {
        if (q->value == value)
        {
            p->next = q->next;
            // Node *n;
            // n = q->next;
            // q = n;
            p = p->next;

            free(q);
            q = nullptr;
            break;
        }
        else
        {
            p = q;
            q = q->next;
        }
    }
    for (Node *m = head->next; m->value != -1; m = m->next)
    {
        printf("%d ", m->value);
    }
    printf("\n");
    list_free(head);
    return 0;
}
