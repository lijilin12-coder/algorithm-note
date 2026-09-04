#include <iostream>
#include <vector>

using namespace std;

int cal_n_cnt(int n)
{
    int cnt = 1;
    while(n /= 10)
    {
        cnt++;
    }
    return cnt;
}

int main()
{
    int n;
    cin >> n;

    cout << cal_n_cnt(1);
    return 0;
}