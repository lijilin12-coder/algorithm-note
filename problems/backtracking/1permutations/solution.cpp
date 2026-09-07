// 提示：回溯法。维护 path（当前排列）和 used 数组（标记已使用的数字）；
// 每一层遍历所有数字，挑一个未使用的：加入 path、标记 used、递归，
// 回来时 pop_back 并取消标记（回溯）；path 长度等于 n 时输出当前排列。
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int>> results;
void f(const vector<int>& nums, vector<int> current, int depth, set<int> flags)
{
    if (depth >= nums.size())
    {
        results.push_back(current);
        return;
    }
    // 尝试摆
    for(int num : nums)
    {
        if (flags.find(num) == flags.end()) {
            // 摆入
            flags.insert(num);
            current.push_back(num);
            f(nums, current, depth+1, flags);

            // 取出
            flags.erase(num);
            current.pop_back();
        }
    }
}


vector<vector<int>> permute(vector<int>& nums) {
    f(nums, vector<int>(), 0, set<int>());
    return results;
}


int main()
{
    int n = 0;
    cin >> n;
    
    vector<int> nums;
    for (int i = 1; i <= n; ++i) {
        int cnt = 0;
        cin >> cnt;
        nums.push_back(cnt);
    }
    vector<vector<int>> result = permute(nums);
    for (const auto& permutation : result) {
        for (int num : permutation) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}