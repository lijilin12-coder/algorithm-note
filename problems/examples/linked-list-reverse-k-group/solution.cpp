#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *reverseKGroup(struct ListNode *head, int k)
{
    if (head == NULL || k <= 1)
    {
        return head;
    }
    ListNode *dummy = (ListNode *)malloc(sizeof(ListNode));
    dummy->next = head;
    dummy->val = 0;
    ListNode *left = dummy;
    int cnt = 0;
    ListNode *right = head;
    ListNode *p = nullptr;
    ListNode *q = nullptr;
    ListNode *last = nullptr;
    while (right != NULL)
    {
        cnt++;
        if (cnt % k == 0)
        {
            right = right->next;
            p = left->next;
            last = left->next;
            left->next = NULL;
            while (p != right)
            {
                q = p->next;
                p->next = left->next;
                left->next = p;
                p = q;
            }
            last->next = right;
            left = last;
        }
        else
        {
            right = right->next;
        }
    }
    return dummy->next;
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

    int k;
    scanf("%d", &k);

    struct ListNode *result = reverseKGroup(dummy.next, k);

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
