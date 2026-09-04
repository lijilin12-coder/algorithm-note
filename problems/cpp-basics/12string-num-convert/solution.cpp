#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;

    cin >> n;
    string *s = new string[n];
    for (int i = 0; i < n; i++)
    {
        cin >> *s;
        if (i < n - 1)
        {
            s += 1;
        }
    }
    int ret = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int m = stoi(*s);
        ret += m;
        s--;
    }
    string z = to_string(ret);
    cout << z;
    return 0;
}