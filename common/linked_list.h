#ifndef ALGORITHM_NOTE_COMMON_LINKED_LIST_H
#define ALGORITHM_NOTE_COMMON_LINKED_LIST_H

#include <cstddef>

// 通用单链表实现，供题目解答直接 #include "linked_list.h" 复用，避免重复实现。
//
// 用法示例:
//   LinkedList<int> list;
//   list.push_back(1);
//   list.push_back(2);
//   for (auto* node = list.head(); node != nullptr; node = node->next) {
//       // 使用 node->value
//   }

template <typename T>
class LinkedList {
public:
    struct Node {
        T value;
        Node* next = nullptr;
    };

    LinkedList() = default;

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    ~LinkedList() {
        clear();
    }

    void push_back(const T& value) {
        Node* new_node = new Node{value, nullptr};
        if (head_ == nullptr) {
            head_ = new_node;
        } else {
            tail_->next = new_node;
        }
        tail_ = new_node;
        ++size_;
    }

    void clear() {
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    Node* head() const { return head_; }
    std::size_t size() const { return size_; }
    bool empty() const { return head_ == nullptr; }

private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};

#endif // ALGORITHM_NOTE_COMMON_LINKED_LIST_H
