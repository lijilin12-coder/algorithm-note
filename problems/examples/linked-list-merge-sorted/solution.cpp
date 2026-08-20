#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

static void read_list(Node* head) {
    int value;
    while (scanf("%d", &value) == 1) {
        if (value == -1) {
            break;
        }
        list_push_back(head, value);
    }
}

int main() {
    Node* list_a = list_create();
    Node* list_b = list_create();

    read_list(list_a);
    read_list(list_b);

    Node* merged = list_create();
    // 在这里实现你的代码，将 list_a 和 list_b 合并为一个新的链表 merged
    


    // 输出合并后的链表
    int first = 1;
    for (Node* p = merged->next; p != NULL; p = p->next) {
        if (!first) {
            printf(" ");
        }
        printf("%d", p->value);
        first = 0;
    }
    printf("\n");

    list_free(list_a);
    list_free(list_b);
    list_free(merged);
    return 0;
}
