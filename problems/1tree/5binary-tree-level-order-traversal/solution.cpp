#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "tree.h"
using namespace std;

class Solution
{
public:
    vector<vector<int>> ans;
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        if (root == nullptr)
            return ans;
        queue<TreeNode *> q;
        q.push(root);
        while (q.empty() == false)
        {
            vector<int> currentlevel;
            int levelsize = q.size();
            for (int i = 0; i < levelsize; ++i)
            {
                TreeNode *node = q.front();
                q.pop();
                if (node->left != nullptr)
                {
                    q.push(node->left);
                }
                if (node->right != nullptr)
                {
                    q.push(node->right);
                }
                currentlevel.push_back(node->val);
            }
            ans.push_back(currentlevel);
        }
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
    vector<vector<int>> res = sol.levelOrder(root);

    cout << res.size() << "\n";
    for (auto &level : res)
    {
        for (size_t i = 0; i < level.size(); ++i)
        {
            if (i)
                cout << ' ';
            cout << level[i];
        }
        cout << "\n";
    }

    tree_free(root);
    return 0;
}
