#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        
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
    cout << sol.change(amount, coins) << '\n';
    return 0;
}
