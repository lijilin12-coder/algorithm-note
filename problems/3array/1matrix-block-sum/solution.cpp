#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        build_presum(mat);
        vector<vector<int>> ans(_row, vector<int>(_col, 0));
        for (int r = 0; r < _row; r++)
        {
            for (int c = 0; c < _col; c++)
            {
                ans[r][c] = get_range_sum(r-k, c-k, r+k, c+k);
            }
            
        }
        return ans;
        
    }
private:
    void build_presum(const vector<vector<int>>& mat)
    {
        if (mat.empty()) return;
        _col = mat.size();
        _row = mat[0].size();

        for (int r = 1; r <= _row; ++r)
        {
            for (int c = 1; c <= _col; ++c)
            {
                _pre_sum[r][c] = _pre_sum[r][c-1] + _pre_sum[r-1][c] - _pre_sum[r-1][c-1] + mat[r-1][c-1];
            }
        }
    }

    int get_min(int x, int min_num = 0)
    {
        return max(x, min_num);
    }

    int get_max(int x, int max_num){
        return min(x, max_num);
    }

    int get_range_sum(int x1, int y1, int x2, int y2){
        x1 =  get_min(x1, 0);
        y1 = get_min(y1, 0);
        x2 = get_max(x2, _col);
        y2 = get_max(y2, _row);

        return _pre_sum[y2][x2] + _pre_sum[y2+1][x1] 
                + _pre_sum[y1][x2+1] -_pre_sum[y1][x1];
    }

private:
    vector<vector<int>> _pre_sum;
    int _col = 0;
    int _row = 0;
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
