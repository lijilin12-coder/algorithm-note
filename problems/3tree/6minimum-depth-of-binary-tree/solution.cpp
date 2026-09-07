#include <iostream>
#include <string>
#include <vector>
#include "tree.h"
using namespace std;

class Solution {
public:
    int minDepth(TreeNode* root) {
        // 在这里实现你的代码

    }
};

int main() {
    vector<string> tokens;
    string tok;
    while (cin >> tok) tokens.push_back(tok);

    TreeNode* root = build_tree(tokens);

    Solution sol;
    int res = sol.minDepth(root);
    cout << res << "\n";

    tree_free(root);
    return 0;
}
