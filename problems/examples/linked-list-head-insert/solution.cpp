#include <stdio.h>
#include "linked_list.h"

int main() {
    Node* head = list_create();
    /*在这里实现你的代码*/
    while (1) {
        int value;
        scanf("%d", &value);
        if (value == -1) {
            break; // 输入 -1 结束输入
        }
        list_push_back(head, value); // 在链表尾部插入新节点
    }

    
    
    list_free(head);
    return 0;
}
