#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> amount_minstep(amount + 1, amount + 1);
        amount_minstep[0] = 0;
        for (int i = 0; i < amount_minstep.size(); ++i)
        {
            for (const auto &c : coins)
            {
                if (i - c < 0)
                    continue;
                amount_minstep[i] = min(amount_minstep[i], amount_minstep[i - c] + 1);
            }
        }
        return amount_minstep[amount] == amount + 1 ? -1 : amount_minstep[amount];
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
