#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int value;
    struct _node* next; // 指针 --> （地址 + 类型）
} Node;

typedef Node* NodePtr; // NodePtr 是 Node* 的别名

Node* add(Node* head, int number);

int main()
{
    Node* head = NULL;
    int number;
    do
    {
        scanf("%d", &number);
        if (number != -1)
        {
            // 调用一个函数来创建一个新节点，并将其插入到链表的末尾
            add(&head, number);
        }
    } while (number != -1);
    return 0;
}
/*
    1. 函数在传递参数时，发生了什么？
        - add(head, number); // 调用
    2. 函数在返回时，发生了什么？
        - return head; // 返回

*/

void add(NodePtr* pHead, int number)
{
    Node* head = *pHead; // 解引用，获取实际的 head 指针
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
        // head = new_node;
        *pHead = new_node; // 修改 head 指针的值，使其指向新节点
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
    return head;
}