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
    i = 0;
    for (i = 0; i < m.size(); i++)
    {
        if (m[i] == target)
        {
            m.erase(m.begin() + i);
        }
    }
    i = 0;
    for (i = 0; i <= m.size(); i++)
    {
        if (i < m.size() - 1)
        {
            cout << m[i] << " ";
        }
        else if (i == m.size() - 1 && i == 0)
        {
            cout << "\n";
        }

        else if (i == m.size() - 1 && 1 != 0)
        {
            cout << m[i];
            break;
        }
    }

    return 0;
}