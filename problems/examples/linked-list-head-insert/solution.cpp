#include <stdio.h>
#include "linked_list.h"

void list_push_front(Node *head, int value)
{
    Node *new_node;
    new_node = (Node *)malloc(sizeof(Node));
    Node *last = head->next;
    new_node->value = value;
    new_node->next = last;
    head->next = new_node;
}

int main()
{
    Node *head = list_create();
    /*在这里实现你的代码*/
    int line, number, last;
    scanf("%d", &line);
    int i = 0;
    while (1)
    {
        int value;
        i++;
        if (i <= line)
        {
            scanf("%d", &number);
            list_push_front(head, number);
        }
        if (i == line + 1)
        {
            int lastnumber;
            scanf("%d", &lastnumber);
            list_push_front(head, lastnumber);
            break;
        }
    }
    for (Node *m = head->next; m != NULL; m = m->next)
    {
        printf("%d ", m->value);
    }
    printf("\n");

    list_free(head);
    return 0;
}
