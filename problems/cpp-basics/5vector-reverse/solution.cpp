// 提示：用 vector<int> 读入 n 个数，调用 reverse(v.begin(), v.end()) 反转后输出。
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    vector<int> m;
    int a, b;
    int i = 0;
    cin >> a;
    while (i < a)
    {
        i++;
        cin >> b;
        m.push_back(b);
    }
    reverse(m.begin(), m.end());
    int row = 0;
    for (row = 0; row < m.size(); row++)
    {
        cout << m[row];
        if (row < m.size() - 1)
        {
            cout << " ";
        }
    }
    return 0;
}