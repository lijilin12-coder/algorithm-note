#include <iostream>
#include <vector>

using namespace std;

const int N = 10;
vector<vector<int>> ans;
vector<bool> visited(N, false); // 是否已经用过这个数了

void dfs(int n, vector<int> cur_ans)
{
    //1. 检查
    if(cur_ans.size() == n)
    {
        ans.push_back(cur_ans);
        return;
    }

    for(int i =1; i <=n; ++i)
    {
        // 2. 判断能够递归
        if(visited[i] == true) continue;

        // 3. 使用当前元素
        cur_ans.push_back(i);
        visited[i] = true;    

        // (1)  --> (1, 2, 3 )  (1, 3, 2)
        // (2)  --> (2, 1, 3)   (2. 3. 1)
        // 4. 递归搜索
        dfs(n, cur_ans);

        // 5. 恢复
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