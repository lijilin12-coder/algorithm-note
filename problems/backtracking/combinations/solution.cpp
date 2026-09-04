// 提示：backtrack(start) 选够 k 个数时输出，否则让 i 从 start 到 n 依次尝试加入并回溯。
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {

    }
};

int main() {
    int n, k;
    cin >> n >> k;

    Solution sol;
    vector<vector<int>> res = sol.combine(n, k);

    cout << res.size() << "\n";
    for (auto& c : res) {
        for (size_t i = 0; i < c.size(); i++) {
            if (i > 0) cout << " ";
            cout << c[i];
        }
        cout << "\n";
    }
    return 0;
}
