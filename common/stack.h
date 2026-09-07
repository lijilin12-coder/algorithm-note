#ifndef ALGORITHM_NOTE_COMMON_STACK_H
#define ALGORITHM_NOTE_COMMON_STACK_H

#include <stdlib.h>

// 栈（纯 C 风格、链表实现），供题目解答直接 #include "stack.h" 复用，贴近
// 数据结构学习时"用链表实现栈"的写法：栈顶始终是链表的头节点，入栈/出栈都
// 只操作头节点，均为 O(1)。
//
// 数据域为 void*（通用指针），既可以存整数（配合 (void*)(intptr_t)value 做
// 转换），也可以直接存节点指针（例如迭代式 DFS 时存 TreeNode*），便于配合
// tree.h/nary_tree.h 一起使用。
//
// 用法示例（迭代式 DFS，存节点指针）:
//   Stack* s = stack_create();
//   stack_push(s, root);
//   while (!stack_empty(s)) {
//       TreeNode* node = (TreeNode*)stack_top(s);
//       stack_pop(s);
//       if (node->left != NULL) stack_push(s, node->left);
//       if (node->right != NULL) stack_push(s, node->right);
//   }
//   stack_free(s);

// 栈内部的链表节点，仅供 stack.h 自身使用。
typedef struct StackNode {
    void* value;
    struct StackNode* next;
} StackNode;

// 栈：top 指向栈顶节点；栈为空时 top 为 NULL。
typedef struct {
    StackNode* top;
} Stack;

// 创建一个空栈。
static inline Stack* stack_create(void) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

// 判断栈是否为空。
static inline int stack_empty(Stack* s) {
    return s->top == NULL;
}

// 入栈：在栈顶插入一个新元素。
static inline void stack_push(Stack* s, void* value) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->value = value;
    node->next = s->top;
    s->top = node;
}

// 查看栈顶元素的值。调用前需自行用 stack_empty 确认栈非空。
static inline void* stack_top(Stack* s) {
    return s->top->value;
}

// 出栈：移除栈顶元素并释放其占用的内存。调用前需自行用 stack_empty 确认栈非空。
static inline void stack_pop(Stack* s) {
    StackNode* node = s->top;
    s->top = node->next;
    free(node);
}

// 释放整个栈（含尚未出栈的全部节点）。
static inline void stack_free(Stack* s) {
    while (!stack_empty(s)) {
        stack_pop(s);
    }
    free(s);
}

#endif // ALGORITHM_NOTE_COMMON_STACK_H

