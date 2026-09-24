# 两个字符串的最小ASCII删除和（Minimum ASCII Delete Sum for Two Strings）

> LeetCode: [712. Minimum ASCII Delete Sum for Two Strings](https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/) / [712. 两个字符串的最小ASCII删除和](https://leetcode.cn/problems/minimum-ascii-delete-sum-for-two-strings/)

## 题目描述

给定两个字符串 `s1` 和 `s2`，返回使两个字符串相等所需删除字符的
**ASCII 值的最小和**。

## 输入格式

第一行：字符串 `s1`。
第二行：字符串 `s2`。

## 输出格式

一行一个整数：使两个字符串相等所需删除字符的 ASCII 值的最小和。

## 样例

样例 1：

输入：
```
sea
eat
```

输出：
```
231
```

解释：在 `"sea"` 中删除 `"s"` 并将 `"s"` 的值（115）加入总和。
在 `"eat"` 中删除 `"t"` 并将 116 加入总和。
结束时，两个字符串相等，115 + 116 = 231 就是符合条件的最小和。

样例 2：

输入：
```
delete
leet
```

输出：
```
403
```

解释：在 `"delete"` 中删除 `"dee"` 字符串变成 `"let"`，
将 100[d] + 101[e] + 101[e] 加入总和。在 `"leet"` 中删除 `"e"` 将
101[e] 加入总和。
结束时，两个字符串都等于 `"let"`，结果即为 100 + 101 + 101 + 101 = 403。
如果改为将两个字符串转换为 `"lee"` 或 `"eet"`，我们会得到 433 或 417
的结果，比答案更大。

## 数据范围

- `1 <= s1.length, s2.length <= 1000`
- `s1` 和 `s2` 由小写英文字母组成

## 函数签名（LeetCode 风格）

```cpp
int minimumDeleteSum(string s1, string s2) {

}
```
