# 94. 递归实现排列型枚举

- [题目](https://www.acwing.com/problem/content/description/96/)
- [提交记录](https://www.acwing.com/problem/content/submission/96/)
- [讨论](https://www.acwing.com/problem/content/discussion/index/96/1/)
- [题解](https://www.acwing.com/problem/content/solution/96/1/)
- [视频讲解](https://www.acwing.com/problem/content/video/96/)

## 题目描述

把 1∼n 这 n 个整数排成一行后随机打乱顺序，输出所有可能的次序。

## 输入格式

一个整数 n。

## 输出格式

按照从小到大的顺序输出所有方案，每行 1 个。

首先，同一行相邻两个数用一个空格隔开。

其次，对于两个不同的行，对应下标的数一一比较，字典序较小的排在前面。

## 数据范围

`1≤n≤9`

## 样例

输入：
```
3
```

输出：
```
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```

## 提示

- 这是回溯法的经典入门题：维护一条「路径」（当前正在构造的排列），
  并用一个 `used` 数组标记哪些数字已经被放进路径里。
- 递归的每一层，从小到大遍历 `1~n`，挑一个还没用过的：放进路径、标记已用、
  递归下一层，回来时撤销这两步（这就是「回溯」）。
- 当路径长度等于 `n` 时，说明凑出了一个完整排列，把它输出。
- 只要遍历顺序是从小到大，输出自然就是字典序，无需额外排序。
