# 俄罗斯套娃信封问题（Russian Doll Envelopes）

> LeetCode: [354. Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/) / [354. 俄罗斯套娃信封问题](https://leetcode.cn/problems/russian-doll-envelopes/)

## 题目描述

给你一个二维整数数组 `envelopes`，其中 `envelopes[i] = [w_i, h_i]`，表示第 `i`
个信封的宽度和高度。

当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封
里，如同俄罗斯套娃一样。

请计算**最多能有多少个**信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放
到另一个信封里面）。

注意：不允许旋转信封。

## 输入格式

第一行一个整数 `n`，表示信封个数。

接下来 `n` 行，每行两个整数 `w` 和 `h`，表示一个信封的宽度和高度。

## 输出格式

一行一个整数：最多能嵌套的信封个数。

## 样例

样例 1：

输入：
```
4
5 4
6 4
6 7
2 3
```

输出：
```
3
```

解释：最多信封的个数为 `3`，组合为 `[2,3] => [5,4] => [6,7]`。

样例 2：

输入：
```
3
1 1
1 1
1 1
```

输出：
```
1
```

## 数据范围

- `1 <= envelopes.length <= 10^5`
- `envelopes[i].length == 2`
- `1 <= w_i, h_i <= 10^5`

## 提示

- 这是 [2longest-increasing-subsequence](../2longest-increasing-subsequence/problem.md) 的
  进阶变形：套娃要求宽、高都严格更大，本质是在二维上找最长严格递增序列。
- **关键转换**：先按宽度 `w` **升序**排序；宽度相同的信封按高度 `h`
  **降序**排序。排序后，只需要在**高度序列**上求最长严格递增子序列
  （LIS），就是答案。
- 为什么宽度相同时高度要降序？因为同宽的信封不能互相嵌套，降序排列可以
  避免 LIS 把同宽的多个信封误判为可嵌套的递增序列。
- 数据规模 `n` 达到 `10^5`，`O(n^2)` 的朴素 LIS 会超时，需要用**贪心 + 二分
  查找**的 `O(n log n)` LIS 解法（维护递增子序列末尾的最小值数组，二分查找
  替换位置）。

## 函数签名（LeetCode 风格）

```cpp
int maxEnvelopes(vector<vector<int>>& envelopes) {

}
```
