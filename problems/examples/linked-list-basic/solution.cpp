#include <iostream>
#include "linked_list.h"

int main() {
    Node* head = list_create();
    int number;
    while (std::cin >> number) {
        if (number == -1) {
            break;
        }
        list_push_back(head, number);
    }

    long long sum = 0;
    for (Node* p = head->next; p != nullptr; p = p->next) {
        sum += p->value;
    }

    std::cout << sum << std::endl;

    list_free(head);
    return 0;
}
