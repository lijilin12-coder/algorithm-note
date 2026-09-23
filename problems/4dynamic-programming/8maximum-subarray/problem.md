# 最大子数组和（Maximum Subarray）

> LeetCode: [53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) / [53. 最大子数组和](https://leetcode.cn/problems/maximum-subarray/)

## 题目描述

给你一个整数数组 `nums`，请你找出一个具有最大和的**连续子数组**（子数
组最少包含一个元素），返回其最大和。

子数组是数组中的一个连续部分。

## 输入格式

第一行一个整数 `n`，表示数组长度。

第二行 `n` 个整数，用空格分隔，表示数组 `nums`。

## 输出格式

一行一个整数：最大子数组和。

## 样例

样例 1：

输入：
```
9
-2 1 -3 4 -1 2 1 -5 4
```

输出：
```
6
```

解释：连续子数组 `[4,-1,2,1]` 的和最大，为 `6`。

样例 2：

输入：
```
1
1
```

输出：
```
1
```

样例 3：

输入：
```
5
5 4 -1 7 8
```

输出：
```
23
```

解释：连续子数组 `[5,4,-1,7,8]` 的和最大，为 `23`。

## 数据范围

- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`

## 函数签名（LeetCode 风格）

```cpp
int maxSubArray(vector<int>& nums) {

}
```
