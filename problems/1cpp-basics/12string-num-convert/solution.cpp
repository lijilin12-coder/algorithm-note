// 提示：stoi 把字符串转成 int；累加后用 to_string 把 int 转回字符串。
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        string numStr;
        cin >> numStr;
        sum += stoi(numStr);
    }

    cout << to_string(sum) << endl;

    return 0;
}
