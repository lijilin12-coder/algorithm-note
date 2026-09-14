#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        // 在这里开始实现你的代码
    }
};

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> mat(m, vector<int>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];

    int k;
    cin >> k;

    Solution sol;
    vector<vector<int>> ans = sol.matrixBlockSum(mat, k);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) cout << ' ';
            cout << ans[i][j];
        }
        cout << '\n';
    }
    return 0;
}
