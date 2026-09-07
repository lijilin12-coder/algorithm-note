#include <stdio.h>
#include "linked_list.h"

int main() {
    Node* head = list_create();
    /*在这里实现你的代码*/
    while (1) {
        int val;
        scanf("%d", &val);
        if (val == -1) {
            break; // 输入 -1 结束输入
        }
        list_push_back(head, val); // 在链表尾部插入新节点
    }

    
    
    list_free(head);
    return 0;
}
