#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    int a;
    vector<int> m;
    while (cin >> a)
    {
        m.push_back(a);
    }
    sort(m.begin(), m.end());
    for (int i = 0; i < m.size(); i++)
    {
        if (i < m.size() - 1)
        {

            cout << m[i] << " ";
        }
        else
        {
            cout << m[i];
        }
    }

    return 0;
}