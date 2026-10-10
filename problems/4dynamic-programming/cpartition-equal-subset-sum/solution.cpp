#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    Solution sol;
    cout << (sol.canPartition(nums) ? "YES" : "NO") << '\n';
    return 0;
}
