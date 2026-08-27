#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *partition(struct ListNode *head, int x)
{
    ListNode *small = (ListNode *)malloc(sizeof(ListNode));
    small->next = NULL;
    small->val = 0;
    ListNode *a = small;
    ListNode *large = (ListNode *)malloc(sizeof(ListNode));
    large->next = NULL;
    large->val = 0;
    ListNode *b = large;
    ListNode *result = (ListNode *)malloc(sizeof(ListNode));
    result->next = NULL;
    result->val = 0;

    for (ListNode *p = head; p != NULL; p = p->next)
    {
        if (p->val < x)
        {
            a->next = p;
            a = a->next;
        }

        if (p->val >= x)
        {
            b->next = p;
            b = b->next;
        }
    }
    b->next = NULL;
    a->next = large->next;
    return small->next;
}

int main()
{
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode *tail = &dummy;

    int value;
    while (scanf("%d", &value) == 1)
    {
        if (value == -1)
        {
            break;
        }
        struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
        node->val = value;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }

    int x;
    scanf("%d", &x);

    struct ListNode *result = partition(dummy.next, x);

    int first = 1;
    for (struct ListNode *p = result; p != NULL; p = p->next)
    {
        if (!first)
        {
            printf(" ");
        }
        printf("%d", p->val);
        first = 0;
    }
    printf("\n");

    for (struct ListNode *p = result; p != NULL;)
    {
        struct ListNode *next = p->next;
        free(p);
        p = next;
    }

    return 0;
}
