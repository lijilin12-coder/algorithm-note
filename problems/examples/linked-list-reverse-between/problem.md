# 反转链表 II

来源：[LeetCode 92. 反转链表 II](https://leetcode.cn/problems/reverse-linked-list-ii/description/)

## 题目描述

给你单链表的头指针 `head` 和两个整数 `left` 和 `right`，其中 `left <= right`。
请你反转从位置 `left` 到位置 `right` 的链表节点，返回反转后的链表。

## 示例 1

```
输入：head = [1,2,3,4,5], left = 2, right = 4
输出：[1,4,3,2,5]
```

## 示例 2

```
输入：head = [5], left = 1, right = 1
输出：[5]
```

## 提示

- 链表中节点数目为 `n`
- `1 <= n <= 500`
- `-500 <= Node.val <= 500`
- `1 <= left <= right <= n`

进阶：你可以使用一趟扫描完成反转吗？

## 输入格式

第一行：以空格分隔的整数序列，表示链表 `head`，以 `-1` 结尾（`-1` 本身不计入链表）。

第二行：两个用空格分隔的整数 `left` 和 `right`。

## 输出格式

一行，反转后链表中所有元素，用空格分隔。

## 样例

输入：
```
1 2 3 4 5 -1
2 4
```

输出：
```
1 4 3 2 5
```

## 数据范围

- 链表长度 `1 <= n <= 500`
- 节点值 `-500 <= Node.val <= 500`
- `1 <= left <= right <= n`

## 函数签名（LeetCode 风格）

```c
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {

}
```
