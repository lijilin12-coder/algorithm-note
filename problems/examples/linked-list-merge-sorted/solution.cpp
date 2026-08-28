#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

static void read_list(Node *head)
{
    int value;
    while (scanf("%d", &value) == 1)
    {
        if (value == -1)
        {
            break;
        }
        list_push_back(head, val);
    }
}

int main()
{
    Node *list_a = list_create();
    Node *list_b = list_create();

    read_list(list_a);
    read_list(list_b);

    Node *pa = list_a->next;
    Node *pb = list_b->next;
    Node *merged = list_create();

    while (pa != NULL && pb != NULL)
    {
        if (pa->value <= pb->value)
        {
            list_push_back(merged, pa->value);
            pa = pa->next;
        }
        else
        {
            list_push_back(merged, pb->value);
            pb = pb->next;
        }
    }

    while (pa != NULL)
    {
        list_push_back(merged, pa->value);
        pa = pa->next;
    }
    while (pb != NULL)
    {
        list_push_back(merged, pb->value);
        pb = pb->next;
    }

    // 输出合并后的链表
    int first = 1;
    for (Node *p = merged->next; p != NULL; p = p->next)
    {
        if (!first)
        {
            printf(" ");
        }
        printf("%d", p->val);
        first = 0;
    }
    printf("\n");

    list_free(list_a);
    list_free(list_b);
    list_free(merged);
    return 0;
}
