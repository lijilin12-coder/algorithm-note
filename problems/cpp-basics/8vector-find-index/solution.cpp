// 提示：用 find(v.begin(), v.end(), target) 查找，配合 it - v.begin() 计算下标，未找到输出 -1。
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int main()
{
    int n, target;
    vector<int> m;
    cin >> n >> target;
    int i = 0;
    int in;
    while (i < n)
    {
        i++;
        cin >> in;
        m.push_back(in);
    }
    auto it = find(m.begin(), m.end(), target);
    if (it == m.end())
    {
        cout << "-1" << endl;
    }
    else
    {
        cout << it - m.begin() << endl;
    }
    return 0;
}
