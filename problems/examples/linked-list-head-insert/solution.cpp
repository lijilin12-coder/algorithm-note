#include <stdio.h>
#include "linked_list.h"

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    Node* head = list_create();

    for (int i = 0; i < n; ++i) {
        int value;
        scanf("%d", &value);
        Node* node = (Node*)malloc(sizeof(Node));
        node->value = value;
        node->next = head->next;
        head->next = node;
    }

    int x;
    scanf("%d", &x);
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = x;
    node->next = head->next;
    head->next = node;

    int first = 1;
    for (Node* p = head->next; p != NULL; p = p->next) {
        if (!first) {
            printf(" ");
        }
        printf("%d", p->value);
        first = 0;
    }
    printf("\n");

    list_free(head);
    return 0;
}
