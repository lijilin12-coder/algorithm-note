#include <iostream>
#include <vector>

using namespace std;

const int N = 10;
vector<vector<int>> ans;
vector<bool> visited(N, false); // 是否已经用过这个数了

void dfs(int n, vector<int> cur_ans)
{
    //检查
    if(cur_ans.size() == n)
    {
        ans.push_back(cur_ans);
        return;
    }

    for(int i =1; i <=n; ++i)
    {
        if(visited[i] == true) continue;

        // 使用这个数
        cur_ans.push_back(i);
        visited[i] = true;

        dfs(n, cur_ans);

        cur_ans.pop_back();
        visited[i] = false;
    }

}



int main()
{
    int n;
    cin >> n;
    vector<int> cur_ans;
    dfs(n, cur_ans);

    for(auto & items : ans)
    {
        for(auto & item : items)
        {
            cout << item << " ";
        }
        cout << endl;
    }
    return 0;
}