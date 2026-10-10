#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
    }
};

int main()
{
    int n, target;
    cin >> n >> target;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    Solution sol;
    cout << sol.findTargetSumWays(nums, target) << '\n';
    return 0;
}
