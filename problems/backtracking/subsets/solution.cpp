// 提示：backtrack(start) 先输出当前 path，再让 i 从 start 到 n-1 依次尝试加入 nums[i] 并回溯。
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> cur_ans;
        backtrace(nums, cur_ans, 0);
        return ans;
    }

private:
    void backtrace(const vector<int>& nums, vector<int> cur_ans, int depth)
    {
        if(depth >= nums.size())
        {
            return;
        }
        ans.push_back(cur_ans);

        for (int i = depth; i < nums.size(); ++i)
        {
            cur_ans.push_back(nums[i]);
            backtrace(nums, cur_ans, depth+1); // 放置
            cur_ans.pop_back();
        }
    }

private:
    vector<vector<int>> ans;
};

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto& x : nums) cin >> x;

    Solution sol;
    vector<vector<int>> res = sol.subsets(nums);

    cout << res.size() << "\n";
    for (auto& s : res) {
        cout << s.size();
        for (int x : s) cout << " " << x;
        cout << "\n";
    }
    return 0;
}
