#include <iostream>
#include <vector>
using namespace std;
int N = 5;
long result = 0;

bool is_win(const vector<vector<int>>& board,int target, int row, int col)
{
    // 只需要判断经过 (row,col) 这颗新落子的四个方向上，是否连出了 5 个同色棋子。
    // 这样无论 N 是多大，都只在真的连成 5 子时才判定为赢（N < 5 时永远不可能触发）。
    int dirs[4][2] = {{0,1},{1,0},{1,1},{1,-1}};
    for (auto& d : dirs)
    {
        int dr = d[0], dc = d[1];
        int count = 1;

        int r = row + dr, c = col + dc;
        while (r >= 0 && r < N && c >= 0 && c < N && board[r][c] == target)
        {
            ++count;
            r += dr; c += dc;
        }

        r = row - dr; c = col - dc;
        while (r >= 0 && r < N && c >= 0 && c < N && board[r][c] == target)
        {
            ++count;
            r -= dr; c -= dc;
        }

        if (count >= 5) return true;
    }
    return false;
}

void play(vector<vector<int>>& board, int idx, int whiteLeft, int blackLeft)
{
    if (idx == N*N)
    {
        result++;
        return;
    }
    int row = idx / N, col = idx % N;

    // 分支一：这一格填白棋（颜色是选出来的，不是由 idx 的奇偶决定）
    if (whiteLeft > 0)
    {
        board[row][col] = 1;
        if (!is_win(board, 1, row, col))
        {
            play(board, idx+1, whiteLeft-1, blackLeft);
        }
        board[row][col] = 3;
    }

    // 分支二：这一格填黑棋
    if (blackLeft > 0)
    {
        board[row][col] = 0;
        if (!is_win(board, 0, row, col))
        {
            play(board, idx+1, whiteLeft, blackLeft-1);
        }
        board[row][col] = 3;
    }
}

int main()
{
    result = 0;
    vector<vector<int>> board(N, vector<int>(N, 3));
    int whiteCount = (N*N+1)/2; // 白棋先手，数量向上取整
    int blackCount = N*N/2;
    play(board, 0, whiteCount, blackCount);
    cout << result << "\n";
    return 0;
}
