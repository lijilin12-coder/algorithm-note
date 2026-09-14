# 和可被 K 整除的子数组（Subarray Sums Divisible by K）

> LeetCode: [974. Subarray Sums Divisible by K](https://leetcode.com/problems/subarray-sums-divisible-by-k/) / [974. 和可被 K 整除的子数组](https://leetcode.cn/problems/subarray-sums-divisible-by-k/)

## 题目描述

给你一个整数数组 `nums` 和一个整数 `k`，请你返回其中元素之和可被 `k` 整除的（**连续**）子数组的个数。

## 输入格式

第一行两个整数 `n` 和 `k`，用空格分隔，分别表示数组长度和除数。

第二行 `n` 个整数，用空格分隔，表示数组 `nums`。

## 输出格式

一行一个整数：和可被 `k` 整除的子数组个数。

## 样例

输入：
```
6 5
4 5 0 -2 -3 1
```

输出：
```
7
```

解释：有 7 个子数组满足其元素之和可被 `k = 5` 整除：
`[4, 5, 0, -2, -3, 1]`、`[5]`、`[5, 0]`、`[5, 0, -2, -3]`、`[0]`、`[0, -2, -3]`、`[-2, -3]`。

## 数据范围

- `1 <= nums.length <= 3 * 10^4`
- `-10^4 <= nums[i] <= 10^4`
- `2 <= k <= 10^4`

## 提示

- 和 [7subarray-sum-equals-k](../7subarray-sum-equals-k/problem.md) 一样是「前缀和 +
  哈希表」的套路：子数组 `j+1..i` 的和为 `prefix[i] - prefix[j]`，能被 `k` 整除
  等价于 `prefix[i] % k == prefix[j] % k`。
- 于是不需要记录前缀和的具体数值，只需要记录**前缀和模 k 的余数**出现的
  次数：遍历时对每个位置的余数 `r`，把哈希表中 `r` 已出现的次数累加到答案，
  再把 `r` 出现次数加一。
- **易错点（负数取模）**：C++ 中负数对正数取模结果可能是负数或 0（例如
  `-2 % 5 == -2`），而这里需要的是数学意义上落在 `[0, k)` 的余数。计算余数
  时要写成 `((sum % k) + k) % k`，避免把 `-2` 和 `3` 当成两个不同的余数。
- 同样需要初始化余数 `0` 出现 `1` 次，处理从数组开头就整除的子数组。

## 函数签名（LeetCode 风格）

```cpp
int subarraysDivByK(vector<int>& nums, int k) {

}
```
