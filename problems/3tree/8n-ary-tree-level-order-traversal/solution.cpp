#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "nary_tree.h"
using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        // 在这里实现你的代码

    }
};

int main() {
    vector<string> tokens;
    string tok;
    while (cin >> tok) tokens.push_back(tok);

    Node* root = build_nary_tree(tokens);

    Solution sol;
    vector<vector<int>> res = sol.levelOrder(root);

    cout << res.size() << "\n";
    for (auto& level : res) {
        for (size_t i = 0; i < level.size(); ++i) {
            if (i) cout << ' ';
            cout << level[i];
        }
        cout << "\n";
    }

    nary_tree_free(root);
    return 0;
}
