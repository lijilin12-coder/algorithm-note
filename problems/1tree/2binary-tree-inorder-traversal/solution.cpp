#include <iostream>
#include <string>
#include <vector>
#include "tree.h"
using namespace std;

class Solution
{
public:
    vector<int> ans;
    vector<int> inorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return ans;
        inorderTraversal(root->left);
        ans.push_back(root->val);
        inorderTraversal(root->right);
        return ans;
    }
};

int main()
{
    vector<string> tokens;
    string tok;
    while (cin >> tok)
        tokens.push_back(tok);

    TreeNode *root = build_tree(tokens);

    Solution sol;
    vector<int> res = sol.inorderTraversal(root);

    for (size_t i = 0; i < res.size(); ++i)
    {
        if (i)
            cout << ' ';
        cout << res[i];
    }
    cout << '\n';

    tree_free(root);
    return 0;
}
