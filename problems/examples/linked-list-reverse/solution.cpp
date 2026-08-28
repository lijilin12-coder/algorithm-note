#include <iostream>
#include "linked_list.h"

Node *reverse_list(Node *head)
{
    Node *p = head;
    Node *q = head->next;
    Node *newhead = (Node *)malloc(sizeof(Node));
    newhead->value = -1;
    newhead->next = nullptr;

    while (p != NULL)
    {
        q = p->next;
        p->next = newhead->next;
        newhead->next = p;
        p = q;
    }
    return newhead->next;
}

int main()
{
    Node *sentinel = list_create();
    int value;

    while (std::cin >> value && value != -1)
    {
        list_push_back(sentinel, value);
    }

    sentinel->next = reverse_list(sentinel->next);

    Node *current = sentinel->next;
    while (current != NULL)
    {
        if (current != sentinel->next)
        {
            std::cout << ' ';
        }
        std::cout << current->val;
        current = current->next;
    }
    std::cout << '\n';

    list_free(sentinel);
    return 0;
}