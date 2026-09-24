# 最长回文子串（Longest Palindromic Substring）

> LeetCode: [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) / [5. 最长回文子串](https://leetcode.cn/problems/longest-palindromic-substring/)

## 题目描述

给你一个字符串 `s`，找到 `s` 中最长的**回文子串**。

- 回文：正着读和反着读都一样的字符串。
- 子串：字符串中连续的非空字符序列。

## 输入格式

一行：字符串 `s`。

## 输出格式

一行：`s` 中最长的回文子串。

> 说明：LeetCode 上若存在多个等长的最长回文子串，返回任意一个即可；本地测试
> 用例（`tests/`）只选取答案唯一的输入，因此输出需与 `.ans` 完全一致。

## 样例

样例 1：

输入：
```
babad
```

输出：
```
bab
```

解释：`"aba"` 同样是符合题意的答案（该样例答案不唯一，未收录进 `tests/`）。

样例 2：

输入：
```
cbbd
```

输出：
```
bb
```

## 数据范围

- `1 <= s.length <= 1000`
- `s` 仅由数字和英文字母组成

## 函数签名（LeetCode 风格）

```cpp
string longestPalindrome(string s) {

}
```
