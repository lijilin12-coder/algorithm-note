#ifndef ALGORITHM_NOTE_COMMON_TREE_H
#define ALGORITHM_NOTE_COMMON_TREE_H

#include <cstdlib>
#include <queue>
#include <string>
#include <vector>

// 二叉树节点定义（与 LeetCode 官方一致），供题目解答直接 #include "tree.h"
// 复用。这里只提供与具体算法无关的建树/释放样板代码，遍历本身（先序/中序/
// 后序/层序）留给各题目自己实现。
//
// 输入格式约定：一行按层序（BFS）排列的 token，用空格分隔；token 为整数表示
// 节点值，token 为字符串 "null" 表示这个位置没有节点（不会再展开它的子节
// 点）。根节点是第一个 token；若树为空，输入不包含任何 token。
//
// 用法示例:
//   vector<string> tokens;
//   string tok;
//   while (cin >> tok) tokens.push_back(tok);
//   TreeNode* root = build_tree(tokens);
//   // ... 使用 root ...
//   tree_free(root);

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 按层序 token 列表建树；tokens 为空表示空树，返回 nullptr。
inline TreeNode* build_tree(const std::vector<std::string>& tokens) {
    if (tokens.empty()) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(atoi(tokens[0].c_str()));
    std::queue<TreeNode*> pending;
    pending.push(root);

    size_t i = 1;
    while (!pending.empty() && i < tokens.size()) {
        TreeNode* node = pending.front();
        pending.pop();

        if (i < tokens.size()) {
            const std::string& left_token = tokens[i++];
            if (left_token != "null") {
                node->left = new TreeNode(atoi(left_token.c_str()));
                pending.push(node->left);
            }
        }
        if (i < tokens.size()) {
            const std::string& right_token = tokens[i++];
            if (right_token != "null") {
                node->right = new TreeNode(atoi(right_token.c_str()));
                pending.push(node->right);
            }
        }
    }

    return root;
}

// 递归释放整棵树。
inline void tree_free(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    tree_free(root->left);
    tree_free(root->right);
    delete root;
}

#endif
