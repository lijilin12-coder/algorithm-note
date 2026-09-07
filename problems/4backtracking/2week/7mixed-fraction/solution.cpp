/*
N= A + C/B

1. check 怎么写：
1. (N-A) * B = C
2. 1-9全包含，并且不重复。

2. 如何递归：
    2.1 递归a   // 求 cal_a(i, 9) i>0
    2.2 递归b

*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int N = 10;
int ans = 0;
int n;
// vector<bool> visited(10, false);
bool visited[N], backup[N];
// vector<bool> visited(10, false);

// bool check(int a, int b)
// {
//     if (a == 0 || b == 0 ) return false;

//     int c = (n-a)*b;
//     auto temp = visited;
//     do
//     {
//         int p = c % 10;
//         if (p == 0) return false;
//         if (temp[p]) return false;
//         temp[p] = true;
//     } while (c/=10);
//     for(int i = 1;i<=9; ++i)
//     {
//         if (!temp[i]) return false;
//     }
    
//     return true;
// }
bool check(int a, int c)
{
    long long b = n * (long long)c - a * c;

    if (!a || !b || !c) return false;

    memcpy(backup, visited, sizeof visited);
    // auto backup = visited;
    while (b)
    {
        int x = b % 10;     // 取个位
        b /= 10;    // 个位删掉
        if (!x || backup[x]) return false;
        backup[x] = true;
    }

    for (int i = 1; i <= 9; i ++ )
        if (!backup[i])
            return false;

    return true;
}




void cal_b(int a, int cur_b, int u)
{
    if (u>9) return; 
    if (check(a, cur_b))
    {
        ans++;
    }

    for(int i = 1;i <= 9; ++i)
    {
        if (visited[i]) continue;
        visited[i] = true;
        cal_b(a, cur_b*10+i, u+1);
        visited[i] = false;
    }


}

void cal_a(int cur_a, int u)
{
    if (cur_a >= n) return;
    if (cur_a > 0)
    {
        cal_b(cur_a, 0, u);
    }

    for (int i = 1; i<=9; ++i)
    {
        if (visited[i]) continue;
        visited[i] = true;
        cal_a(cur_a*10+i, u+1);
        visited[i] = false;
    }
}

int main()
{
    cin >>n;
    cal_a(0, 0);
    cout << ans << endl;
    return 0;
}