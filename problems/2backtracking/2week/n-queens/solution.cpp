#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> ans;
    vector<vector<int>> dirs = {
        {0,1},
        {1,0},
        {1,1},
        {1,-1}
    };

    int cnt_q = 0;
    vector<string> board;
    bool check(int n, int row, int col, char target)
    {
        for(auto& dir : dirs)
        {
            int dr = dir[0],  dc = dir[1];
            int r = row + dr, c = col + dc;
            int cnt = 0;
            while(r >= 0 && c>= 0 && r < n && c < n)
            {
                if (board[r][c] == target)
                {
                    cnt++;
                    if (cnt >= 1) return false;
                }
                r += dr;
                c += dc;
            }
            r = row - dr, c = col - dc;
            while(r >= 0 && c>= 0 && r < n && c < n)
            {
                if (board[r][c] == target)
                {
                    cnt++;
                    if (cnt >= 1) return false;
                }
                r -= dr;
                c -= dc;
            }
        }
        return true;
    }


    void dfs(int n, int row)
    {
        if (row == n)
        {
            ans.push_back(board);
            return;
        }

        for(int c = 0; c < n; ++c)
        {
            if (check(n, row, c, 'Q') == false) continue;
            
            board[row][c] = 'Q';
            dfs(n, row+1);
            board[row][c] = '.';
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        board.resize(n, string(n,'.'));
        cnt_q = 0;
        dfs(n, 0);
        return ans;

    }
};

int main() {
    int n;
    cin >> n;

    Solution sol;
    vector<vector<string>> res = sol.solveNQueens(n);

    // LeetCode 允许任意顺序，这里按每行皇后所在列排序，保证输出稳定
    auto key = [](const vector<string>& board) {
        vector<size_t> cols;
        for (const string& row : board) cols.push_back(row.find('Q'));
        return cols;
    };
    sort(res.begin(), res.end(), [&](const vector<string>& a, const vector<string>& b) {
        return key(a) < key(b);
    });

    cout << res.size() << '\n';
    for (size_t i = 0; i < res.size(); ++i) {
        if (i > 0) cout << '\n';
        for (const string& row : res[i]) cout << row << '\n';
    }
    return 0;
}
