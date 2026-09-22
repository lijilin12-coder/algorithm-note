# 单词拆分 II（Word Break II）

> LeetCode: [140. Word Break II](https://leetcode.com/problems/word-break-ii/) / [140. 单词拆分 II](https://leetcode.cn/problems/word-break-ii/description/)

## 题目描述

给你一个字符串 `s` 和一个字符串列表 `wordDict` 作为字典。请你在字符串
`s` 中增加空格来构建一个句子，使得句子中所有的单词都在词典中出现。以
**任意顺序**返回所有这些可能的句子。

注意：词典中的同一个单词可以在分句中被重复使用多次。

## 输入格式

第一行：字符串 `s`。

第二行一个整数 `n`，表示 `wordDict` 中单词的个数。

第三行 `n` 个字符串，用空格分隔，表示 `wordDict`（按输入顺序排列，顺序
会影响下面规定的输出顺序）。

## 输出格式

第一行输出可行句子的总数。

接下来按照下面规定的回溯顺序，每种句子占一行，句子内单词之间用单个空
格分隔：

从下标 `start = 0` 开始，依次按 `wordDict` 给定的输入顺序尝试每个单
词 `w`：如果 `s` 从 `start` 开始的子串恰好等于 `w`，且 `start +
w.length() == s.length()`，说明拼出了一个完整句子，记录当前路径；否
则递归处理 `start + w.length()`，把递归返回的每个后缀句子依次前面拼
上 `w` 后记录下来。多个候选单词之间按 `wordDict` 的顺序依次尝试，同
一层内先尝试到的单词产生的句子排在前面。

如果不存在任何可行句子，只输出一行 `0`。

## 样例

样例 1：

输入：
```
catsanddog
5
cat cats and sand dog
```

输出：
```
2
cat sand dog
cats and dog
```

样例 2：

输入：
```
pineapplepenapple
5
apple pen applepen pine pineapple
```

输出：
```
3
pine apple pen apple
pine applepen apple
pineapple pen apple
```

样例 3：

输入：
```
catsandog
5
cats dog sand and cat
```

输出：
```
0
```

## 数据范围

- `1 <= s.length <= 20`
- `1 <= wordDict.length <= 1000`
- `1 <= wordDict[i].length <= 10`
- `s` 和 `wordDict[i]` 仅由小写英文字母组成
- `wordDict` 中的所有字符串**互不相同**

## 提示

- 可以用记忆化搜索：`dfs(start)` 返回从 `start` 开始能拼出的所有句子
  列表（按 `wordDict` 顺序拼接得到），用 `unordered_map<int,
  vector<string>>` 缓存每个 `start` 的结果，避免重复计算。
- `dfs(s.length())` 的 base case 返回一个只含空字符串的列表，方便最
  后一个单词直接输出自身而不多带空格。
- 也可以先用类似「单词拆分」的判断预处理出哪些 `start` 能够拼到字符
  串末尾，剪枝掉无法完成拼接的分支。

## 函数签名（LeetCode 风格）

```cpp
vector<string> wordBreak(string s, vector<string>& wordDict) {

}
```
