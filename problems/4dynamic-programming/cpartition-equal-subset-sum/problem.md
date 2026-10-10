# 分割等和子集（Partition Equal Subset Sum）

> LeetCode: [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) / [416. 分割等和子集](https://leetcode.cn/problems/partition-equal-subset-sum/)

## 题目描述

给你一个**只包含正整数**的**非空**数组 `nums`。请你判断是否可以将这个数组分割成
两个子集，使得两个子集的元素和相等。

## 输入格式

第一行一个整数 `n`，表示数组长度。

第二行 `n` 个整数，用空格分隔，表示数组 `nums`。

## 输出格式

一行：如果可以分割成两个元素和相等的子集，输出 `YES`；否则输出 `NO`。

## 样例

样例 1：

输入：
```
4
1 5 11 5
```

输出：
```
YES
```

解释：数组可以分割成 `[1, 5, 5]` 和 `[11]`。

样例 2：

输入：
```
4
1 2 3 5
```

输出：
```
NO
```

解释：数组不能分割成两个元素和相等的子集。

## 数据范围

- `1 <= nums.length <= 200`
- `1 <= nums[i] <= 100`

## 提示

- 设总和为 `sum`。若 `sum` 为奇数，直接返回 `false`；否则问题转化为：能否从
  `nums` 中选出若干个数，使其和恰好为 `sum / 2`。
- 这是一个 **0/1 背包**问题：每个数最多选一次，背包容量为 `sum / 2`。
- 定义 `dp[j]` 表示能否选出若干个数使其和恰好为 `j`，`dp[0] = true`。
- 状态转移：`dp[j] = dp[j] || dp[j - num]`，对每个 `num`，`j` 从 `sum / 2`
  **逆序**遍历到 `num`，保证每个数只被使用一次。

## 函数签名（LeetCode 风格）

```cpp
bool canPartition(vector<int>& nums) {

}
```
