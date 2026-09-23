# 编辑距离（Edit Distance）

> LeetCode: [72. Edit Distance](https://leetcode.com/problems/edit-distance/) / [72. 编辑距离](https://leetcode.cn/problems/edit-distance/)

## 题目描述

给你两个单词 `word1` 和 `word2`，请返回将 `word1` 转换成 `word2` 所使用
的最少操作数。

你可以对一个单词进行如下三种操作：

- 插入一个字符
- 删除一个字符
- 替换一个字符

## 输入格式

第一行：字符串 `word1`。
第二行：字符串 `word2`。

## 输出格式

一行一个整数：将 `word1` 转换成 `word2` 所需的最少操作数。

## 样例

样例 1：

输入：
```
horse
ros
```

输出：
```
3
```

解释：
```
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
```

样例 2：

输入：
```
intention
execution
```

输出：
```
5
```

解释：
```
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')
```

## 数据范围

- `0 <= word1.length, word2.length <= 500`
- `word1` 和 `word2` 由小写英文字母组成

## 函数签名（LeetCode 风格）

```cpp
int minDistance(string word1, string word2) {

}
```
