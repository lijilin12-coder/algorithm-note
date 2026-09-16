#include <iostream>
#include <string>
#include <vector>
#include "nary_tree.h"
using namespace std;

class Solution
{
public:
    vector<int> ans;
    vector<int> postorder(Node *root)
    {
        if (root == nullptr)
            return ans;
        for (Node *child : root->children)
        {
            postorder(child);
        }
        ans.push_back(root->val);
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
    vector<int> res = sol.postorder(root);

    for (size_t i = 0; i < res.size(); ++i)
    {
        if (i)
            cout << ' ';
        cout << res[i];
    }
    cout << '\n';

    nary_tree_free(root);
    return 0;
}
