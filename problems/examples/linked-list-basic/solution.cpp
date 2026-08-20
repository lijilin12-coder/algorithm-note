#include <stdio.h>
#include "common/linked_list.h"

int main() {
    Node* head = list_create(); // 创建一个空链表，head 为哨兵头指针
    while (1) {
        int value;
        scanf("%d", &value);
        if (value == -1) {
            break; // 输入 -1 结束输入
        }
        list_push_back(head, value); // 在链表尾部插入新节点
    }

    int sum = 0;
    for(Node* p = head->next; p != NULL; p = p->next) {
        sum += p->value; // 计算链表中所有节点的值的和
    }

    printf("%d\n", sum); // 输出链表中所有节点的值的和

    return 0;
}
