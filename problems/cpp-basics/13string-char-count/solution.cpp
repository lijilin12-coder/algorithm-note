// 提示：<cctype> 提供 isdigit/isalpha 判断单个字符类型。
#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int N = 5;
const vector<vector<int>> dirs = {
    {0, 0},{0,1}, {0,-1}, {1, 0}, {-1,0}
    
};
void reverse(vector<string>& board, int row, int col);
void reverse_all_neighber(vector<string>& board, int row, int col);
void reverse(vector<string>& board, int row, int col)
{
    if (row < 0 || col < 0 || row >= N || col >= N) return;
    board[row][col] = board[row][col] == '1' ? '0':'1';
}


void reverse_all_neighber(vector<string>& board, int row, int col)
{
    for(const auto& ds : dirs)
    {
       reverse(board, row + ds[0], col + ds[1]); 
    }
}




int main()
{
    int n;
    cin >> n;
    while(n--)
    {
        vector<string> board;
        int min_step = 7;
        for(int i = 0; i < N; ++i)
        {
            string row;
            cin >> row;
            board.push_back(row);
        }
        
        for(int op = 0; op < 1<<N; ++op)
        {
            int cur_step = 7;
            for(int i = 0; i < N; ++i)
            {
                if (op >> i & 1 && board[0][i] == '0')
                {
                    reverse_all_neighber(board, 0, i);
                    cur_step++;
                }
                
                // 处理 0 ~ N-2行
                for (int row = 0; row < N-1; ++row)
                {
                    for (int col = 0; col < N; ++col)
                    {
                        if (board[row][col] == '0')
                        {
                            reverse_all_neighber(board, row+1, col);
                            cur_step++;
                        }
                    }
                }
                
                //判断最后一行是否全为1
                bool all_light = true;
                for(int col  = 0; col < N; col++)
                {
                    if (board[N-1][col] == '0')
                    {
                        all_light = false;
                        break;
                    }
                }
                if (all_light){
                    min_step = cur_step < min_step ? cur_step : min_step;
                }
                
            }
            min_step = min_step > 6 ? -1 : min_step;
            cout << min_step << endl;
        }
    }
    
    
    return 0;
}