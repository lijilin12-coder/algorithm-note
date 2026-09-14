#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    // 在这里实现你的代码

}

int main() {
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* tail = &dummy;

    int value;
    while (scanf("%d", &value) == 1) {
        if (value == -1) {
            break;
        }
        struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = value;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }

    int left, right;
    scanf("%d %d", &left, &right);

    struct ListNode* result = reverseBetween(dummy.next, left, right);

    int first = 1;
    for (struct ListNode* p = result; p != NULL; p = p->next) {
        if (!first) {
            printf(" ");
        }
        printf("%d", p->val);
        first = 0;
    }
    printf("\n");

    for (struct ListNode* p = result; p != NULL; ) {
        struct ListNode* next = p->next;
        free(p);
        p = next;
    }

    return 0;
}
