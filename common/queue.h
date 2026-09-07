#ifndef ALGORITHM_NOTE_COMMON_QUEUE_H
#define ALGORITHM_NOTE_COMMON_QUEUE_H

#include <stdlib.h>

// 队列（纯 C 风格、链表实现），供题目解答直接 #include "queue.h" 复用，贴近
// 数据结构学习时"用链表实现队列"的写法：一个队列结构体维护队首/队尾指针，
// 每个元素是一个链表节点。
//
// 数据域为 void*（通用指针），既可以存整数（配合 (void*)(intptr_t)value 做
// 转换），也可以直接存节点指针（例如层序遍历二叉树/多叉树时存 TreeNode*），
// 便于配合 tree.h/nary_tree.h 一起使用。
//
// 用法示例（存整数）:
//   Queue* q = queue_create();
//   queue_push(q, (void*)(intptr_t)1);
//   queue_push(q, (void*)(intptr_t)2);
//   while (!queue_empty(q)) {
//       int value = (int)(intptr_t)queue_front(q);
//       queue_pop(q);
//       // 使用 value
//   }
//   queue_free(q);
//
// 用法示例（存节点指针，如层序遍历二叉树）:
//   Queue* q = queue_create();
//   queue_push(q, root);
//   while (!queue_empty(q)) {
//       TreeNode* node = (TreeNode*)queue_front(q);
//       queue_pop(q);
//       if (node->left != NULL) queue_push(q, node->left);
//       if (node->right != NULL) queue_push(q, node->right);
//   }
//   queue_free(q);

// 队列内部的链表节点，仅供 queue.h 自身使用。
typedef struct QueueNode {
    void* value;
    struct QueueNode* next;
} QueueNode;

// 队列：front 指向队首节点，rear 指向队尾节点，size 是当前元素个数；
// 队列为空时 front/rear 均为 NULL，size 为 0。
typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;

// 创建一个空队列。
static inline Queue* queue_create(void) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

// 判断队列是否为空。
static inline int queue_empty(Queue* q) {
    return q->front == NULL;
}

// 入队：在队尾追加一个新元素。
static inline void queue_push(Queue* q, void* value) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->value = value;
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = node;
        q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
    ++q->size;
}

// 返回队列中的元素个数。
static inline int queue_size(Queue* q) {
    return q->size;
}

// 查看队首元素的值。调用前需自行用 queue_empty 确认队列非空。
static inline void* queue_front(Queue* q) {
    return q->front->value;
}

// 出队：移除队首元素并释放其占用的内存。调用前需自行用 queue_empty 确认队列非空。
static inline void queue_pop(Queue* q) {
    QueueNode* node = q->front;
    q->front = node->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(node);
    --q->size;
}

// 释放整个队列（含尚未出队的全部节点）。
static inline void queue_free(Queue* q) {
    while (!queue_empty(q)) {
        queue_pop(q);
    }
    free(q);
}

#endif // ALGORITHM_NOTE_COMMON_QUEUE_H

