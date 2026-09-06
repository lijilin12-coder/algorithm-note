// 递归实现指数型枚举：对 1~n 每个数依次决定选/不选，递归到底时输出已选的数。
// 按「先不选、再选」的顺序递归；n 个二元决策共 2^n 种方案（含空集）。
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<bool> chosen;

void dfs(int u)
{
    if (u == n)
    {
        bool first = true;
        for (int i = 0; i < n; ++i)
        {
            if (chosen[i])
            {
                if (!first) cout << " ";
                cout << i + 1;
                first = false;
            }
        }
        cout << endl;
        return;
    }

    chosen[u] = false;
    dfs(u + 1);

    chosen[u] = true;
    dfs(u + 1);
}

int main()
{
    cin >> n;
    chosen.assign(n, false);
    dfs(0);
    return 0;
}
