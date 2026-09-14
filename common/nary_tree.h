#ifndef ALGORITHM_NOTE_COMMON_NARY_TREE_H
#define ALGORITHM_NOTE_COMMON_NARY_TREE_H

#include <cstdlib>
#include <queue>
#include <string>
#include <vector>

// N 叉树节点定义（与 LeetCode 官方一致），供题目解答直接 #include
// "nary_tree.h" 复用。这里只提供与具体算法无关的建树/释放样板代码，遍历本
// 身（前序/后序/层序）留给各题目自己实现。
//
// 输入格式约定（层序遍历序列化，每组子节点前都有一个 null 分隔）：一行按
// 层序（BFS）排列的 token，用空格分隔；第一个 token 是根节点的值；随后依次
// 处理队列中的每个节点：先跳过一个 "null"（表示这个节点的子节点列表开
// 始），再读取若干个整数作为它的子节点值，直到遇到下一个 "null" 为止（这个
// "null" 属于下一个节点，不在这里消耗）。若根节点为空，输入不包含任何
// token。
//
// 例如树，根节点 1 的子节点是 [3, 2, 4]，节点 3 的子节点是 [5, 6]，其余节点
// 都是叶子，对应输入 "1 null 3 2 4 null 5 6"。
//
// 用法示例:
//   vector<string> tokens;
//   string tok;
//   while (cin >> tok) tokens.push_back(tok);
//   Node* root = build_nary_tree(tokens);
//   ...
//   nary_tree_free(root);

struct Node {
    int val;
    std::vector<Node*> children;
    Node() : val(0) {}
    Node(int _val) : val(_val) {}
    Node(int _val, std::vector<Node*> _children) : val(_val), children(_children) {}
};

// 按层序 token 列表建 N 叉树；tokens 为空表示空树，返回 nullptr。
inline Node* build_nary_tree(const std::vector<std::string>& tokens) {
    if (tokens.empty()) {
        return nullptr;
    }

    Node* root = new Node(atoi(tokens[0].c_str()));
    std::queue<Node*> pending;
    pending.push(root);

    size_t i = 1;
    while (!pending.empty() && i < tokens.size()) {
        Node* parent = pending.front();
        pending.pop();

        if (i < tokens.size() && tokens[i] == "null") {
            ++i;
        }
        while (i < tokens.size() && tokens[i] != "null") {
            Node* child = new Node(atoi(tokens[i++].c_str()));
            parent->children.push_back(child);
            pending.push(child);
        }
    }

    return root;
}

// 递归释放整棵树。
inline void nary_tree_free(Node* root) {
    if (root == nullptr) {
        return;
    }
    for (Node* child : root->children) {
        nary_tree_free(child);
    }
    delete root;
}

#endif
