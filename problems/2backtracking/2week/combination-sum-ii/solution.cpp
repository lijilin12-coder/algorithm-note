// 提示：先排序；backtrack(start, remain) 剩余为 0 时输出；同层跳过与上一次相同的数字避免重复组合。
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {

    }
};

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> candidates(n);
    for (auto& x : candidates) cin >> x;

    Solution sol;
    vector<vector<int>> res = sol.combinationSum2(candidates, target);

    cout << res.size() << "\n";
    for (auto& c : res) {
        cout << c.size();
        for (int x : c) cout << " " << x;
        cout << "\n";
    }
    return 0;
}
