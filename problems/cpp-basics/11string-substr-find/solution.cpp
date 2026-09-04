#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    string s, t;
    int len;
    cin >> s >> len >> t;
    cout << s.substr(0, len) << endl;
    auto it = s.find(t);
    if (it == string::npos)
        cout << "-1" << endl;
    else
        cout << it << endl;

    return 0;
}