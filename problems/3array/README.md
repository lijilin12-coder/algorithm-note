# 数组技巧
## 1. 前缀和
https://labuladong.online/zh/algo/data-structure/prefix-sum/

前缀和主要解决快速求解 [n, n+m] 的和
前缀和的递推公式
$$
\text{presum}[i+1] = \text{presum}[i] +  \text{nums}[i] 
$$

$[n,m]$ 之间的和就等于：
$$
\sum_n^m \text{nums} = \text{presum}[m+1] -\text{presum}[n] 
$$

二维的情况

$$
\begin{bmatrix}
a_{11} & a_{12} & \cdots & a_{1n} \\
a_{21} & a_{22} & \cdots & a_{2n} \\
\vdots & \vdots & \ddots & \vdots \\
a_{n1} & a_{n2} & \cdots & a_{nn}
\end{bmatrix}
$$

$$
\text{presum}[r+1][c+1] = \text{presum}[r-1][c] +  \text{presum}[r][c-1] + \text{nums}[r][c]
$$

$[x1,y1, x2,y2]$ 之间的和就等于：
$$
\sum_n^m \text{nums} = \text{presum}[m+1] -\text{presum}[n] 
$$
$$
\text{presum}[x1:x2][y1:y2] 
= \text{presum}[x2+1][y2+1]
- \text{presum}[x1][y2+1]
- \text{presum}[x2+1][y1]
+ \text{presum}[x1][y1]
$$
