// 提示：substr(起始位置, 长度) 截取子串；find 返回子串首次出现的下标，找不到返回 string::npos。
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s, t;
    int len;
    cin >> s >> len >> t;

    cout << s.substr(0, len) << endl;

    size_t pos = s.find(t);
    if (pos == string::npos)
    {
        cout << -1 << endl;
    } else
    {
        cout << pos << endl;
    }

    return 0;
}
