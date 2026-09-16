#include <iostream>
#include <string>
#include <vector>
#include "tree.h"
using namespace std;

class Solution
{
public:
    vector<int> ans;
    vector<int> preorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return ans;
        ans.push_back(root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
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
    vector<int> res = sol.preorderTraversal(root);

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
