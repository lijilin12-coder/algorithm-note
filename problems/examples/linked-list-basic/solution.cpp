#include <iostream>
#include "linked_list.h"

int main() {
    LinkedList<int> list;
    int number;
    while (std::cin >> number) {
        if (number == -1) {
            break;
        }
        list.push_back(number);
    }

    long long sum = 0;
    for (auto* node = list.head(); node != nullptr; node = node->next) {
        sum += node->value;
    }

    std::cout << sum << std::endl;
    return 0;
}
