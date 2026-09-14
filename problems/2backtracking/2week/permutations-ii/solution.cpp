// 提示：先排序；used 数组标记已选下标；同层遇到 nums[i]==nums[i-1] 且 !used[i-1] 时跳过以去重。
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        _valid = vector<bool>(nums.size(), true);
        vector<int> cur_ans;
        backtrace(nums, cur_ans, 0);
        return _ans;
    }

private:
    void backtrace(const vector<int>& nums, vector<int> cur_ans, int start)
    {
        if(cur_ans.size() == nums.size())
        {
            _ans.push_back(cur_ans);
            return;
        }

        for(int i = 0; i<nums.size(); ++i)
        {
            if (_valid[i] == false) 
            {
                continue;
            }
            if (_valid[i] == true && (i>0 && nums[i-1] == nums[i])) 
            {
                continue;
            }

            cur_ans.push_back(nums[i]);
            _valid[i] = false;

            backtrace(nums, cur_ans, 0);

            _valid[i] = true;
            cur_ans.pop_back();
        }
    }
private:
    vector<vector<int>> _ans;
    vector<bool> _valid;
};

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto& x : nums) cin >> x;

    Solution sol;
    vector<vector<int>> res = sol.permuteUnique(nums);

    cout << res.size() << "\n";
    for (auto& p : res) {
        for (size_t i = 0; i < p.size(); i++) {
            if (i > 0) cout << " ";
            cout << p[i];
        }
        cout << "\n";
    }
    return 0;
}
