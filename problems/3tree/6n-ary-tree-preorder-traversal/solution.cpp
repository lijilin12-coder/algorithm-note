#include <iostream>
#include <string>
#include <vector>
#include "nary_tree.h"
using namespace std;

class Solution {
public:
    vector<int> preorder(Node* root) {
        // 在这里实现你的代码

    }
};

int main() {
    vector<string> tokens;
    string tok;
    while (cin >> tok) tokens.push_back(tok);

    Node* root = build_nary_tree(tokens);

    Solution sol;
    vector<int> res = sol.preorder(root);

    for (size_t i = 0; i < res.size(); ++i) {
        if (i) cout << ' ';
        cout << res[i];
    }
    cout << '\n';

    nary_tree_free(root);
    return 0;
}
