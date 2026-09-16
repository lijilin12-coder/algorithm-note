#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "nary_tree.h"
using namespace std;

class Solution
{
public:
    vector<vector<int>> levelOrder(Node *root)
    {
        vector<vector<int>> ans;
        if (root == nullptr)
            return ans;

        queue<Node *> q;
        int level = 0;

        q.push(root);
        while (q.empty() == false)
        {
            level++;
            vector<int> cur;
            int width = q.size();
            for (int i = 0; i < width; ++i)
            {
                Node *node = q.front();
                q.pop();
                for (Node *child : node->children)
                {
                    q.push(child);
                }
                cur.push_back(node->val);
            }
            ans.push_back(cur);
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

    Node *root = build_nary_tree(tokens);

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

    nary_tree_free(root);
    return 0;
}
