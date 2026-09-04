// 提示：<cctype> 提供 isdigit/isalpha 判断单个字符类型。
#include <string>
#include <cctype>
#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
    string s;
    getline(cin, s);
    int a = 0;
    int b = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]) == 1)
        {
            a++;
        }
        if (isalpha(s[i]) == 1)
        {
            b++;
        }
    }
    cout << a << " " << b;
}
