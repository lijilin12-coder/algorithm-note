// 提示：读入摄氏温度 C，按公式 F = C * 9 / 5 + 32 计算华氏温度，
// 使用 cout << fixed << setprecision(2) 保留两位小数输出。
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    double C, F;
    cin >> C;
    F = C * 9 / 5 + 32;
    cout << fixed << setprecision(2) << F;
    return 0;
}