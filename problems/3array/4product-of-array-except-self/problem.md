# 除了自身以外数组的乘积（Product of Array Except Self）

> LeetCode: [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) / [238. 除了自身以外数组的乘积](https://leetcode.cn/problems/product-of-array-except-self/description/)

## 题目描述

给你一个整数数组 `nums`，返回数组 `answer`，其中 `answer[i]` 等于 `nums` 中**除
了 `nums[i]` 之外其余各元素的乘积**。

- **不要使用除法**，且在 `O(n)` 时间复杂度内完成此题。
- 题目数据保证任意元素的全部前缀元素和后缀的乘积都在 32 位整数范围内。

## 输入格式

第一行一个整数 `n`，表示数组长度。

第二行 `n` 个整数，用空格分隔，表示数组 `nums`。

## 输出格式

一行 `n` 个整数，用空格分隔，表示结果数组 `answer`。

## 样例

输入：
```
4
1 2 3 4
```

输出：
```
24 12 8 6
```

解释：

- `answer[0] = 2 * 3 * 4 = 24`
- `answer[1] = 1 * 3 * 4 = 12`
- `answer[2] = 1 * 2 * 4 = 8`
- `answer[3] = 1 * 2 * 3 = 6`

## 数据范围

- `2 <= nums.length <= 10^5`
- `-30 <= nums[i] <= 30`
- 输入保证 `answer[i]` 在 32 位整数范围内

## 提示

- 对每个下标分别求「左边所有数的乘积」和「右边所有数的乘积」再相乘即可，
  关键是避免重复计算、做到 `O(n)`。
- 可以构造两个辅助数组：`left[i]` 为 `nums[0..i-1]` 的乘积，`right[i]` 为
  `nums[i+1..n-1]` 的乘积，则 `answer[i] = left[i] * right[i]`。
- **进阶**：能否只用 `O(1)` 额外空间？（输出数组不算额外空间。）思路是先用一次
  从左到右的遍历把 `answer[i]` 填成左侧乘积，再用一个变量从右到左累乘右侧乘积
  并就地乘进 `answer[i]`。
- 注意数组里可能有 `0`，但**不能用「总乘积除以当前元素」**的做法（题目禁止除法，
  且遇到 `0` 会出错）。

## 函数签名（LeetCode 风格）

```cpp
vector<int> productExceptSelf(vector<int>& nums) {

}
```
