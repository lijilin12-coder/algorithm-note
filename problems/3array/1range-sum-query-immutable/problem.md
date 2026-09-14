# 区域和检索 - 数组不可变（Range Sum Query - Immutable）

> LeetCode: [303. Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/) / [303. 区域和检索 - 数组不可变](https://leetcode.cn/problems/range-sum-query-immutable/description/)

## 题目描述

给定一个整数数组 `nums`，处理以下类型的多个查询：

计算索引 `left` 和 `right`（包含 `left` 和 `right`）之间的 `nums` 元素的**和**，其中
`left <= right`。

实现 `NumArray` 类：

- `NumArray(vector<int>& nums)` 使用数组 `nums` 初始化对象；
- `int sumRange(int left, int right)` 返回数组 `nums` 中索引 `left` 和 `right`
  之间的元素总和（包含两端），即 `nums[left] + nums[left+1] + ... + nums[right]`。

数组在初始化后**不可修改**，且 `sumRange` 会被**多次调用**。请设计一种方法，让每次
查询都能尽可能快地完成。

## 输入格式

第一行一个整数 `n`，表示数组长度。

第二行 `n` 个整数，用空格分隔，表示数组 `nums`。

第三行一个整数 `q`，表示查询次数。

接下来 `q` 行，每行两个整数 `left right`，表示一次查询。

## 输出格式

`q` 行，每行一个整数，依次输出每次查询 `[left, right]` 区间的元素和。

## 样例

输入：
```
6
-2 0 3 -5 2 -1
3
0 2
2 5
0 5
```

输出：
```
1
-1
-3
```

解释：

- `sumRange(0, 2)` = `(-2) + 0 + 3 = 1`
- `sumRange(2, 5)` = `3 + (-5) + 2 + (-1) = -1`
- `sumRange(0, 5)` = `(-2) + 0 + 3 + (-5) + 2 + (-1) = -3`

## 数据范围

- `1 <= nums.length <= 10^4`
- `-10^5 <= nums[i] <= 10^5`
- `0 <= left <= right < nums.length`
- 最多调用 `10^4` 次 `sumRange` 方法

## 提示

- 如果对每次查询都从头累加，单次查询是 `O(n)`，最坏情况总复杂度 `O(n * q)`，
  当 `n`、`q` 都达到 `10^4` 时会超时。
- 关键观察：数组不可变，而查询很多。可以在初始化时预处理出**前缀和**数组
  `prefix[i] = nums[0] + ... + nums[i-1]`（约定 `prefix[0] = 0`），这样任意区间
  `[left, right]` 的和就是 `prefix[right+1] - prefix[left]`，单次查询 `O(1)`。
- 注意元素可能为负数，前缀和同样适用。

## 函数签名（LeetCode 风格）

```cpp
class NumArray {
public:
    NumArray(vector<int>& nums) {

    }

    int sumRange(int left, int right) {

    }
};
```
