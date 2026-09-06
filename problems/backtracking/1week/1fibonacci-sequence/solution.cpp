#include <iostream>
using namespace std;
const int N = 50;
int ans[50];

int f(int n)
{
    if (ans[n] != -1) return ans[n];
    ans[n] = f(n-1) + f(n-2);;
    return ans[n];
}

int main()
{   
    int n;
    cin >> n;
    for(int i = 0;i<N;++i)
    {
        ans[i] = -1;
    }
    ans[1] = 0;
    ans[2] = 1;
    f(n);
    for(int i = 1; i<=n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
}