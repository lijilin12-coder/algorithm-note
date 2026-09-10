#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ProductOfNumbers {
public:
    ProductOfNumbers() {
        // 在这里实现你的代码（初始化）
    }

    void add(int num) {
        // 在这里实现你的代码
    }

    int getProduct(int k) {
        // 在这里实现你的代码
        return 0;
    }
};

int main() {
    int q;
    cin >> q;

    ProductOfNumbers obj;
    while (q--) {
        string op;
        int x;
        cin >> op >> x;
        if (op == "add") {
            obj.add(x);
        } else { // "getProduct"
            cout << obj.getProduct(x) << '\n';
        }
    }
    return 0;
}
