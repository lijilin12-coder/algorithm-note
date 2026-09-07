// 提示：用 + 拼接字符串，size()/length() 取长度，直接用 == / < 比较字符串大小（字典序）。
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a, b;
    cin >> a >> b;

    cout << a + b << endl;
    cout << a.size() << " " << b.size() << endl;

    if (a == b)
    {
        cout << "equal" << endl;
    } else if (a < b)
    {
        cout << "less" << endl;
    } else
    {
        cout << "greater" << endl;
    }

    return 0;
}
