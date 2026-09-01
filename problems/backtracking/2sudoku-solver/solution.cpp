#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

bool found = false;

vector<unordered_set<char>> rows(9);
vector<unordered_set<char>> cols(9);
vector<unordered_set<char>> boxes(9);

int getBoxIndex(int r, int c)
{
    return (r / 3) * 3 + (c / 3);
}

bool isVaild(int r, int c, char num)
{
    if (rows[r].count(num))
        return false;
    if (cols[c].count(num))
        return false;
    if (boxes[getBoxIndex(r, c)].count(num))
        return false;
    return true;
}

void backtrack(vector<vector<char>> &board, int index)
{
    if (found)
    {
        return;
    }

    int m = 9, n = 9;
    int i = index / n, j = index % n;

    if (index == m * n)
    {
        found = true;
        return;
    }

    if (board[i][j] != '.')
    {
        // 如果有预设数字，不用我们穷举
        backtrack(board, index + 1);
        return;
    }
    for (char ch = '1'; ch <= '9'; ch++)
    {
        // 剪掉
        if (!isVaild(i, j, ch))
            continue;

        // 做选择，把 ch 填入 board[i][j]
        board[i][j] = ch;
        rows[i].insert(ch);
        cols[j].insert(ch);
        boxes[getBoxIndex(i, j)].insert(ch);

        backtrack(board, index + 1);

        if (found)
        {
            // 如果找到一个可行解，立即结束
            // 不要撤销选择，否则 board[i][j] 会被重置为 '.'
            return;
        }

        // 撤销选择，把 board[i][j] 重置为 '.'
        board[i][j] = '.';
        rows[i].erase(ch);
        cols[j].erase(ch);
        boxes[getBoxIndex(i, j)].erase(ch);
    }
}

void solveSudoku(vector<vector<char>> &board)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
            {
                rows[i].insert(board[i][j]);
                cols[j].insert(board[i][j]);
                boxes[getBoxIndex(i, j)].insert(board[i][j]);
            }
        }
    }
    backtrack(board, 0);
}

int main()
{
    vector<vector<char>> vboard;
    for (int i = 0; i < 9; i++)
    {
        string line;
        getline(cin, line);
        vboard.push_back(vector<char>(line.begin(), line.end()));
    }

    solveSudoku(vboard);

    for (int i = 0; i < 9; i++)
    {
        string line(vboard[i].begin(), vboard[i].end());
        cout << line << endl;
    }

    return 0;
}
