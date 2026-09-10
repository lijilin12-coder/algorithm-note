# 最后 K 个数的乘积（Product of the Last K Numbers）

> LeetCode: [1352. Product of the Last K Numbers](https://leetcode.com/problems/product-of-the-last-k-numbers/) / [1352. 最后 K 个数的乘积](https://leetcode.cn/problems/product-of-the-last-k-numbers/description/)

## 题目描述

设计一个算法，该算法接受一个整数流并检索该流中**最后 `k` 个整数的乘积**。

实现 `ProductOfNumbers` 类：

- `ProductOfNumbers()` 用一个空的流初始化对象；
- `void add(int num)` 将数字 `num` 添加到当前数字列表的最后面；
- `int getProduct(int k)` 返回当前数字列表中**最后 `k` 个数字的乘积**。你可以假设当前列表中始终至少包含 `k` 个数字。

题目数据保证：任何时候，任一连续数字序列的乘积都在 32 位整数范围内，不会溢出。

## 输入格式

第一行一个整数 `q`，表示操作次数。

接下来 `q` 行，每行是一个操作，形如：

- `add <num>`：向流末尾添加数字 `num`；
- `getProduct <k>`：查询最后 `k` 个数字的乘积。

## 输出格式

对每个 `getProduct` 操作输出一行，即对应的乘积结果。

## 样例

输入：
```
10
add 3
add 0
add 2
add 5
add 4
getProduct 2
getProduct 3
getProduct 4
add 8
getProduct 2
```

输出：
```
20
40
0
32
```

解释：

- 依次 `add` 后流为 `[3, 0, 2, 5, 4]`；
- `getProduct(2)` = `5 * 4 = 20`；
- `getProduct(3)` = `2 * 5 * 4 = 40`；
- `getProduct(4)` = `0 * 2 * 5 * 4 = 0`；
- 再 `add 8` 后流为 `[3, 0, 2, 5, 4, 8]`，`getProduct(2)` = `4 * 8 = 32`。

## 数据范围

- `0 <= num <= 100`
- `1 <= k <= 4 * 10^4`
- `add` 和 `getProduct` 最多被调用 `4 * 10^4` 次
- 在任何时间点流的乘积都在 32 位整数范围内

## 提示

- 朴素做法是维护整个数字列表，每次 `getProduct(k)` 从末尾往前累乘 `k` 个数，单次
  `O(k)`。当操作很多、`k` 很大时会超时。
- **进阶（O(1) 查询）**：维护一个「前缀积」数组 `pre`，`pre[i]` 表示前 `i` 个数的乘积
  （约定 `pre[0] = 1`）。这样最后 `k` 个数的乘积就是 `pre[n] / pre[n-k]`。
- **关键难点是 `0`**：一旦加入 `0`，之后所有前缀积都会变成 `0`，除法就失效了。
  常见技巧是——每当 `add(0)` 时把前缀积数组**清空重置**为 `{1}`，相当于「以这个 0
  为分界重新开始」。此时若 `getProduct(k)` 需要的 `k` 大于当前前缀积数组长度减一，
  说明这 `k` 个数里必然包含那个 `0`，直接返回 `0`。
- 注意本题允许使用除法（与 238 题不同），因为「除自身以外」的限制在这里不存在。

## 函数签名（LeetCode 风格）

```cpp
class ProductOfNumbers {
public:
    ProductOfNumbers() {

    }

    void add(int num) {

    }

    int getProduct(int k) {

    }
};
```
