#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> path;

void dfs(int start)
{
    // 剩余可选数字不够凑满 m 个，直接剪枝返回
    if ((int)path.size() + (n - start + 1) < m) return;

    if ((int)path.size() == m)
    {
        for (size_t i = 0; i < path.size(); ++i)
        {
            if (i) cout << ' ';
            cout << path[i];
        }
        cout << '\n';
        return;
    }

    for (int i = start; i <= n; ++i)
    {
        path.push_back(i);
        dfs(i + 1);
        path.pop_back();
    }
}

int main()
{
    cin >> n >> m;
    dfs(1);
    return 0;
}
