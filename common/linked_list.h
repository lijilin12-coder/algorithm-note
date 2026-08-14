#ifndef ALGORITHM_NOTE_COMMON_LINKED_LIST_H
#define ALGORITHM_NOTE_COMMON_LINKED_LIST_H

#include <stdlib.h>

// 单链表（纯 C 风格实现），供题目解答直接 #include "linked_list.h" 复用，
// 贴近数据结构课堂/教材中手写链表的写法：结构体 + 一组操作函数。
//
// 节点的数据域固定为 int（不使用泛型/模板），便于初学者理解每一步在做什么。
//
// 用法示例:
//   Node* head = list_create();          // 创建一个空链表，head 为哨兵头指针
//   list_push_back(head, 1);
//   list_push_back(head, 2);
//   for (Node* p = head->next; p != NULL; p = p->next) {
//       // 使用 p->value（从 head->next 开始，head 本身是哨兵节点不存数据）
//   }
//   Node* found = list_find(head, 2);    // 查找值为 2 的节点
//   list_remove(head, 2);                // 删除值为 2 的第一个节点
//   int n = list_length(head);           // 链表长度（不含哨兵节点）
//   list_free(head);                     // 释放整个链表（含哨兵节点）

// 链表节点：value 存数据，next 指向下一个节点（NULL 表示链表结束）。
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// 创建一个空链表，返回一个哨兵头节点（不存放有效数据，next 初始为 NULL）。
// 使用哨兵头节点可以让插入/删除的逻辑不必对"链表为空"这种特殊情况单独处理。
static inline Node* list_create(void) {
    Node* head = (Node*)malloc(sizeof(Node));
    head->value = 0;
    head->next = NULL;
    return head;
}

// 在链表尾部插入一个新节点，值为 value。
static inline void list_push_back(Node* head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;

    // 找到当前的尾节点（next 为 NULL 的节点）。
    Node* last_node = head;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }
    last_node->next = new_node;
}

// 从头开始查找第一个值等于 value 的节点，找到返回该节点指针，找不到返回 NULL。
static inline Node* list_find(Node* head, int value) {
    Node* current = head->next;
    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 删除第一个值等于 value 的节点。找到并删除返回 1，没找到返回 0。
static inline int list_remove(Node* head, int value) {
    Node* prev = head;
    Node* current = head->next;
    while (current != NULL) {
        if (current->value == value) {
            prev->next = current->next;
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

// 返回链表中的节点个数（不含哨兵头节点）。
static inline int list_length(Node* head) {
    int count = 0;
    Node* current = head->next;
    while (current != NULL) {
        ++count;
        current = current->next;
    }
    return count;
}

// 释放整个链表（含哨兵头节点），释放后 head 指针不应再被使用。
static inline void list_free(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

#endif // ALGORITHM_NOTE_COMMON_LINKED_LIST_H

