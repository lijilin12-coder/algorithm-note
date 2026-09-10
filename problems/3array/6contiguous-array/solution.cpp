#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        // 在这里实现你的代码
        return 0;
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    Solution sol;
    cout << sol.findMaxLength(nums) << '\n';
    return 0;
}
