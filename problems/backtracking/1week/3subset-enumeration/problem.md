# 92. 递归实现指数型枚举

- [题目](https://www.acwing.com/problem/content/description/94/)
- [提交记录](https://www.acwing.com/problem/content/submission/94/)
- [讨论](https://www.acwing.com/problem/content/discussion/index/94/1/)
- [题解](https://www.acwing.com/problem/content/solution/94/1/)
- [视频讲解](https://www.acwing.com/problem/content/video/94/)

## 题目描述

从 1∼n 这 n 个整数中随机选取任意多个，输出所有可能的选择方案。

## 输入格式

输入一个整数 n。

## 输出格式

每行输出一种方案。

同一行内的数必须升序排列，相邻两个数用恰好 1 个空格隔开。

对于没有选任何数的方案，输出空行。

本题有自定义校验器（SPJ），各行（不同方案）之间的顺序任意。

## 数据范围

`1≤n≤15`

## 样例

输入：
```
3
```

输出：
```
1
1 2
1 2 3
1 3
2
2 3
3

```

（样例展示中省略了「不选任何数」对应的空行；实际输出共 `2^n` 行，含一行空行。）

## 提示

- 这是回溯法的经典模板题之一（指数型枚举）：对 `1~n` 每个数依次决定「选」或
  「不选」，递归到底（`u == n`）时输出当前已选的数。
- 与排列型枚举不同，这里每个数只有两种状态，而不是在剩余数里挑一个，因此
  递归深度恒为 `n`，总方案数为 `2^n`。
- 按「先不选、再选」的顺序递归，输出天然满足题目要求的顺序（虽然本题是
  SPJ，行间顺序其实不作要求）。
