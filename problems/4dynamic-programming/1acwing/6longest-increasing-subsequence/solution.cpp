#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;
const int N = 1010;
int nums[N];
int mem[N][N];
int n;

/*
3 1 2 1 8 5 6

6 5
1

*/

// /**
//  * Longest increasing subsequence chosen from nums[1..idx],
//  * where every chosen element < nums[max_idx].
//  * @param idx      consider only nums[1..idx]
//  * @param max_idx  index of the element chosen right after (n + 1 = none yet)
//  * @return         the max length
//  */
// int dfs(int idx, int max_idx)
// {
//     if (idx == 0) return 0;
//     if (mem[idx][max_idx] != -1) return mem[idx][max_idx];
//     int max_len = dfs(idx - 1, max_idx);                   // skip nums[idx]
//     if (nums[idx] < nums[max_idx])                         // take nums[idx]
//         max_len = max(max_len, dfs(idx - 1, idx) + 1);
//     return mem[idx][max_idx] = max_len;
// }

/**
 * 从 nums[1...idx] 中选择，并且当前最大值是 nums[max_idx]
 * @return 序列长度
 */
int dfs(int idx, int max_idx)
{
    if(idx == 0) return 0;
    if (mem[idx][max_idx] != -1) return mem[idx][max_idx];
    int max_len = dfs(idx -1 , max_idx); //不选 idx
    if(nums[idx] < nums[max_idx])
    {
        max_len = max(max_len, dfs(idx-1, idx)+1);
    }
    return mem[idx][max_idx] = max_len;
}

int f[N][N]; // 从nums[1...idx]中选择， 并且当前最大值是j 的最长序列
int dp(int n)
{
    for(int i = 1; i<=n; ++i)
    {
        for(int j = i+1; j<=n+1; ++j)
        {
           f[i][j] = f[i-1][j];
           if(nums[i] < nums[j]) {
                f[i][j] = max(f[i][j], f[i-1][i]+1);
           }
        }
    }
    return f[n][n+1];

}

// int f[N][N]; // f[i][j]: 从 nums[1..i] 中选、所选元素都 < nums[j] 的最长上升子序列长度
// int dp(int n)
// {
//     for (int i = 1; i <= n; ++i)
//         for (int j = i + 1; j <= n + 1; ++j)
//         {
//             f[i][j] = f[i-1][j];                              // 不选 nums[i]
//             if (nums[i] < nums[j])                            // 选 nums[i]
//                 f[i][j] = max(f[i][j], f[i-1][i] + 1);
//         }
//     return f[n][n + 1];
// }

int main()
{

    cin >> n;
    for(int i = 1; i<=n; ++i)
    {
        cin >> nums[i];
    }
    nums[n + 1] = INT_MAX;          // sentinel: larger than every number
    memset(mem, -1, sizeof mem);    // -1 = not computed yet
    // cout << dfs(n, n + 1) << endl;
    cout << dp(n) << endl;
    return 0;
}
