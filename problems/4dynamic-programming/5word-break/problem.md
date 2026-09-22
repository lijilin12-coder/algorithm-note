# 单词拆分（Word Break）

> LeetCode: [139. Word Break](https://leetcode.com/problems/word-break/) / [139. 单词拆分](https://leetcode.cn/problems/word-break/)

## 题目描述

给你一个字符串 `s` 和一个字符串列表 `wordDict` 作为字典。请你判断是否可以
利用字典中出现的单词拼接出 `s`。

注意：不要求字典中的单词全部使用，字典中的单词可以重复使用多次。

## 输入格式

第一行：字符串 `s`。

第二行一个整数 `n`，表示 `wordDict` 中单词的个数。

第三行 `n` 个字符串，用空格分隔，表示 `wordDict`。

## 输出格式

一行：如果 `s` 可以由 `wordDict` 中的单词拼接而成，输出 `YES`；否则输出
`NO`。

## 样例

样例 1：

输入：
```
leetcode
2
leet code
```

输出：
```
YES
```

解释：返回 `true`，因为 `"leetcode"` 可以由 `"leet"` 和 `"code"` 拼接
而成。

样例 2：

输入：
```
applepenapple
2
apple pen
```

输出：
```
YES
```

解释：返回 `true`，因为 `"applepenapple"` 可以由 `"apple"`、`"pen"`、
`"apple"` 拼接而成，注意允许字典中的单词重复使用。

样例 3：

输入：
```
catsandog
5
cats dog sand and cat
```

输出：
```
NO
```

## 数据范围

- `1 <= s.length <= 300`
- `1 <= wordDict.length <= 1000`
- `1 <= wordDict[i].length <= 20`
- `s` 和 `wordDict[i]` 仅由小写英文字母组成
- `wordDict` 中的所有字符串**互不相同**

## 函数签名（LeetCode 风格）

```cpp
bool wordBreak(string s, vector<string>& wordDict) {

}
```
