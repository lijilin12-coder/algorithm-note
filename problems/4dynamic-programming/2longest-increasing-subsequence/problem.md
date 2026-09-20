# 最长递增子序列（Longest Increasing Subsequence）

> LeetCode: [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) / [300. 最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/)

## 题目描述

给你一个整数数组 `nums`，找到其中最长严格递增子序列的长度。

子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的
顺序。例如，`[3,6,2,7]` 是数组 `[0,3,1,6,2,2,7]` 的子序列。

## 输入格式

第一行一个整数 `n`，表示数组长度。

第二行 `n` 个整数，用空格分隔，表示数组 `nums`。

## 输出格式

一行一个整数：最长严格递增子序列的长度。

## 样例

样例 1：

输入：
```
8
10 9 2 5 3 7 101 18
```

输出：
```
4
```

解释：最长递增子序列是 `[2, 3, 7, 101]`，长度为 `4`。

样例 2：

输入：
```
6
0 1 0 3 2 3
```

输出：
```
4
```

样例 3：

输入：
```
7
7 7 7 7 7 7 7
```

输出：
```
1
```

## 数据范围

- `1 <= nums.length <= 2500`
- `-10^4 <= nums[i] <= 10^4`

## 提示

- 定义 `dp[i]` 为**以 `nums[i]` 结尾**的最长递增子序列的长度，base case
  `dp[i] = 1`（只包含自身）。
- 状态转移：对每个 `j < i`，如果 `nums[j] < nums[i]`，说明 `nums[i]` 可以
  接在以 `nums[j]` 结尾的子序列后面，`dp[i] = max(dp[i], dp[j] + 1)`。
- 最终答案是 `dp` 数组中的最大值（不是 `dp[n-1]`，因为最长子序列不一定以
  最后一个元素结尾）。
- 这个做法时间复杂度是 `O(n^2)`，数据量下足够通过。
- 进阶：可以用**贪心 + 二分查找**优化到 `O(n log n)`——维护一个数组
  `tails`，`tails[k]` 表示长度为 `k+1` 的递增子序列中结尾最小的值；遍历
  `nums`，用二分查找在 `tails` 中找到第一个 `>= nums[i]` 的位置并替换（找
  不到则追加），最终 `tails` 的长度就是答案。

## 函数签名（LeetCode 风格）

```cpp
int lengthOfLIS(vector<int>& nums) {

}
```
