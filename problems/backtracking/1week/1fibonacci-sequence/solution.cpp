// 斐波那契数列：递推即可，第 3 项开始等于前两项之和，无需回溯。
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    vector<long long> fib(n);
    for (int i = 0; i < n; ++i)
    {
        if (i == 0) fib[i] = 0;
        else if (i == 1) fib[i] = 1;
        else fib[i] = fib[i - 1] + fib[i - 2];
    }

    for (int i = 0; i < n; ++i)
    {
        cout << fib[i];
        if (i != n - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
