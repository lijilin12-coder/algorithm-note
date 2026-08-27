#include <iostream>
#include "linked_list.h"

Node* reverse_list(Node* head) {
    Node* previous = NULL;
    Node* current = head;

    while (current != NULL) {
        Node* next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    return previous;
}

int main() {
    Node* sentinel = list_create();
    int value;

    while (std::cin >> value && value != -1) {
        list_push_back(sentinel, value);
    }

    sentinel->next = reverse_list(sentinel->next);

    Node* current = sentinel->next;
    while (current != NULL) {
        if (current != sentinel->next) {
            std::cout << ' ';
        }
        std::cout << current->value;
        current = current->next;
    }
    std::cout << '\n';

    list_free(sentinel);
    return 0;
}