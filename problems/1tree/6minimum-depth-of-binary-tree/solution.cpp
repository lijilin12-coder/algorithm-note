#include <iostream>
#include <string>
#include <vector>
#include "tree.h"
using namespace std;

class Solution
{
public:
    int minDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        int minleftdepth, minrightdepth;
        if (root->left != nullptr && root->right != nullptr)
        {
            minleftdepth = minDepth(root->left);
            minrightdepth = minDepth(root->right);
            return min(minleftdepth, minrightdepth) + 1;
        }
        else if (root->left)
        {
            minleftdepth = minDepth(root->left);
            return minleftdepth + 1;
        }
        else if (root->right)
        {
            minrightdepth = minDepth(root->right);
            return minrightdepth + 1;
        }
        else
        {
            return 1;
        }
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
    int res = sol.minDepth(root);
    cout << res << "\n";

    tree_free(root);
    return 0;
}
