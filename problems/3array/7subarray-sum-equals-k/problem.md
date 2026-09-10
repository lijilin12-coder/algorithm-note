# 和为 K 的子数组（Subarray Sum Equals K）

> LeetCode: [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) / [560. 和为 K 的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/)

## 题目描述

给你一个整数数组 `nums` 和一个整数 `k`，请你统计并返回**该数组中和为 `k` 的连续子数组的个数**。

## 输入格式

第一行两个整数 `n` 和 `k`，用空格分隔，分别表示数组长度和目标和。

第二行 `n` 个整数，用空格分隔，表示数组 `nums`。

## 输出格式

一行一个整数：和为 `k` 的连续子数组的个数。

## 样例

输入：
```
3 2
1 1 1
```

输出：
```
2
```

解释：和为 `2` 的连续子数组有 `[1, 1]`（下标 `0..1`）和 `[1, 1]`（下标 `1..2`），共 `2` 个。

## 数据范围

- `1 <= nums.length <= 2 * 10^4`
- `-1000 <= nums[i] <= 1000`
- `-10^7 <= k <= 10^7`

## 提示

- 暴力做法枚举所有子数组并求和，时间复杂度 `O(n^2)`，数据量大时会超时。
- **关键转换**：记 `prefix[i]` 为前 `i` 个数的和，则子数组 `j+1..i` 的和为
  `prefix[i] - prefix[j]`。要找和为 `k` 的子数组，等价于找满足
  `prefix[i] - prefix[j] == k` 的下标对 `(i, j)`，即 `prefix[j] == prefix[i] - k`。
- 用哈希表记录**每个前缀和出现的次数**：从左到右遍历时，维护当前前缀和
  `sum`，每到一个位置就查哈希表中 `sum - k` 出现的次数，累加到答案，再把
  当前 `sum` 出现次数加一。
- 小技巧：初始化时把前缀和 `0` 出现 `1` 次存入哈希表，这样处理从数组开头
  就和为 `k` 的子数组时无需特判。
- 与 [6contiguous-array](../6contiguous-array/problem.md) 思路类似，都是「前缀和 +
  哈希表」，但这题统计的是**个数**而非**最长长度**，因此哈希表记录的是**出现次数**
  而不是**首次出现的下标**。

## 函数签名（LeetCode 风格）

```cpp
int subarraySum(vector<int>& nums, int k) {

}
```
