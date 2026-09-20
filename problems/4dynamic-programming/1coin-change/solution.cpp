#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        // 在这里开始实现你的代码
    }
};

int main()
{
    int n, amount;
    cin >> n >> amount;

    vector<int> coins(n);
    for (int i = 0; i < n; ++i)
        cin >> coins[i];

    Solution sol;
    cout << sol.coinChange(coins, amount) << '\n';
    return 0;
}
