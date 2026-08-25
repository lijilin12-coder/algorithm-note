// 提示：string 支持和 vector 一样的迭代器，直接用 reverse(s.begin(), s.end()) 反转。
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    string s;
    cin >> s;

    reverse(s.begin(), s.end());

    cout << s << endl;

    return 0;
}
