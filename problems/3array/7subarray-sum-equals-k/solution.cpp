#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pre_sum(n+1, 0);
        int ans = 0;
        unordered_map<int,int> map;
        map[0]=1;
        for(int i = 0; i < n; i++) {
            pre_sum[i+1] = pre_sum[i] + nums[i];
            if (map.find(pre_sum[i+1]-k) != map.end())
            {
                ans += map[pre_sum[i+1]-k];
            } 
            map[pre_sum[i+1]] ++;
        }
        return ans;
    }
};

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    Solution sol;
    cout << sol.subarraySum(nums, k) << '\n';
    return 0;
}
