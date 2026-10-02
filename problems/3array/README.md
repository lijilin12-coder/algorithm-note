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

## 2. 二分模板（左闭右开写法）

### 2.1 查找一个数
```cpp
int binary_search(int[] nums, int target) {
    // right 初始化为 nums.length
    // 左闭右开的搜索区间
    int left = 0, right = nums.length;

    // 用 < 而不是 <=，因为 left == right 时搜索区间为空
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            // 下一轮搜索区间为 [mid+1, right)
            left = mid + 1;
        } else if (nums[mid] > target) {
            // 下一轮搜索区间为 [left, mid)
            right = mid;
        }
    }
    return -1;
}
```

### 2.2 查找左边界
```cpp
// 搜索左侧边界
int left_bound(vector<int>& nums, int target) {
    if (nums.size() == 0) return -1;
    int left = 0, right = nums.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            // 当找到 target 时，收缩右侧边界
            right = mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid;
        }
    }
    return left;
}
```

### 2.3 查找右边界
```cpp
// 搜索右侧边界
int right_bound(vector<int>& nums, int target) {
    if (nums.size() == 0) return -1;
    int left = 0, right = nums.size();

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            // 当找到 target 时，收缩左侧边界
            left = mid + 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid;
        }
    }
    return left - 1;
}

```

