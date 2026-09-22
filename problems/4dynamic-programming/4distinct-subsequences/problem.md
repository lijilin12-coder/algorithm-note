# 不同的子序列（Distinct Subsequences）

> LeetCode: [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/) / [115. 不同的子序列](https://leetcode.cn/problems/distinct-subsequences/)

## 题目描述

给你两个字符串 `s` 和 `t`，请统计并返回在 `s` 的**子序列**中 `t`
**出现的个数**。

字符串的一个子序列是指从原字符串中删去若干个（也可以不删）字符，且不
改变剩余字符相对位置后组成的新字符串。（例如 `"ACE"` 是 `"ABCDE"` 的一个
子序列，而 `"AEC"` 不是）

## 输入格式

第一行：字符串 `s`。
第二行：字符串 `t`。

## 输出格式

一行一个整数：`s` 的子序列中 `t` 出现的个数。

## 样例

样例 1：

输入：
```
rabbbit
rabbit
```

输出：
```
3
```

解释：如下所示，有 `3` 种可以从 `s` 中得到 `"rabbit"` 的方案。
```
rabbbit
rabbbit
rabbbit
```

样例 2：

输入：
```
babgbag
bag
```

输出：
```
5
```

解释：如下所示，有 `5` 种可以从 `s` 中得到 `"bag"` 的方案。
```
babgbag
babgbag
babgbag
babgbag
babgbag
```

## 数据范围

- `0 <= s.length, t.length <= 1000`
- `s` 和 `t` 由英文字母组成
- 结果保证能用 `32` 位有符号整数存储

## 函数签名（LeetCode 风格）

```cpp
int numDistinct(string s, string t) {

}
```
