# 790. 数的三次方根

- [题目](https://www.acwing.com/problem/content/description/790/)
- [提交记录](https://www.acwing.com/problem/content/submission/790/)
- [讨论](https://www.acwing.com/problem/content/discussion/index/790/1/)
- [题解](https://www.acwing.com/problem/content/solution/790/1/)
- [视频讲解](https://www.acwing.com/problem/content/video/790/)

## 题目描述

给定一个浮点数 `n`，求它的三次方根。

## 输入格式

共一行，包含一个浮点数 `n`。

## 输出格式

共一行，包含一个浮点数，表示问题的解。

注意，结果保留 6 位小数。

## 数据范围

`-10000 <= n <= 10000`

## 样例

输入：
```
1000.00
```

输出：
```
10.000000
```

## 提示

- 直接调用 `cbrt(n)` 虽然能过，但这道题的考点是**在实数轴上用二分法求根**。
- 关键观察：函数 `f(x) = x^3` 在整个实数域上**严格单调递增**，所以方程 `x^3 = n`
  至多只有一个实根，满足二分法「单调性」的前提。
- 先确定一个**一定包含根的搜索区间** `[l, r]`：
  - `n >= 0` 时，根在 `[0, max(1, n)]`；
  - `n < 0` 时，根在 `[min(-1, n), 0]`。
- 每次取中点 `mid = (l + r) / 2`，比较 `mid^3` 与 `n`：
  - `mid^3 > n` 说明 `mid` 偏大，令 `r = mid`；
  - 否则令 `l = mid`。
- 迭代足够多次（例如 100 次），区间长度会缩小到远小于 `1e-6`，此时输出 `(l + r) / 2`
  并保留 6 位小数即为答案。
