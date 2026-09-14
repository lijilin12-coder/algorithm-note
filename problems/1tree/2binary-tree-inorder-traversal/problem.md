# 二叉树的中序遍历

> LeetCode: [94. Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/) / [94. 二叉树的中序遍历](https://leetcode.cn/problems/binary-tree-inorder-traversal/)

## 题目描述

给定一棵二叉树的根节点 `root`，返回它节点值的**中序遍历**结果（左子树 ->
根 -> 右子树）。

## 输入格式

一行，按层序（BFS）排列、用空格分隔的若干个 token：

- token 为整数表示一个节点的值；
- token 为字符串 `null` 表示这个位置没有节点（不会再展开它的子节点）。

第一个 token 是根节点。如果树为空，输入是一个空行（不包含任何 token）。

例如树

```
  1
   \
    2
   /
  3
```

对应输入 `1 null 2 3`。

## 输出格式

一行，依次输出中序遍历得到的节点值，用空格分隔；如果树为空，输出空行。

## 样例

输入：
```
1 null 2 3
```

输出：
```
1 3 2
```

## 数据范围

- 树中节点数目在范围 `[0, 100]` 内
- `-100 <= Node.val <= 100`

## 提示

- 中序遍历的顺序是：先递归遍历左子树，再访问根节点，再递归遍历右子树。
- 你能否分别用递归和迭代（借助栈）两种方式实现？
