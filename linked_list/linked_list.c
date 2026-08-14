#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int value;
    struct _node* next; // 指针 --> （地址 + 类型）
} Node;

int main()
{
    Node* head = NULL;
    int number;
    do
    {
        scanf("%d", &number);
        if (number != -1)
        {
            // Add to linked-list.
            // 1. Create a new node
            Node* new_node = (Node*)malloc(sizeof(Node));

            // 2. 初始化新节点
            new_node->value = number;
            new_node->next = NULL;

            // 3. 将新节点插入到链表的尾部.
            // 3.1 找到尾部
            // 1> 如果链表为空
            if (head == NULL)
            {
                head = new_node;
            } else 
            {
                // 2> 如果链表不为空
                // 找到尾部
                Node* last_node = head;
                while (last_node->next != NULL)
                {
                    last_node = last_node->next;
                }

                // 将新节点插入尾部
                last_node->next = new_node;
            }
        }
    } while (number != -1);
    return 0;
}