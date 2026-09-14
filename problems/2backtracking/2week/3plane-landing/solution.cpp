#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int get_fly_time(const vector<int>& data)
{
    return data[0] + data[1];
}

bool is_plan_succ = true;
void backtrace(
    vector<vector<int>>& datas, 
    vector<bool>& visited, 
    int done_time
)
{
    for (int i = 0; i<datas.size(); ++i)
    {
        // Push
        if (visited[i]) continue;
        is_plan_succ = true;
        int start_time = done_time;
        if (datas[i][0] > done_time)
        {
            start_time = datas[i][0];
        }
        if (get_fly_time(datas[i]) < done_time)
        {
            is_plan_succ = false;
            continue;
        }
        visited[i] = true;
        
        backtrace(datas, visited,start_time + datas[i][2]);
        
        visited[i] = false;
        if(is_plan_succ) return;
    }
}

bool judge(vector<vector<int>>& datas)
{
    sort(datas.begin(), datas.end(), [&]
        (const vector<int>&a, const vector<int>&b){
        if (a[0] + a[1] < b[0] + b[1])
        {
            return true;
        }
        return false;
    });
    vector<bool> visited(datas.size(), false);
    backtrace(datas, visited, 0);
    return is_plan_succ;
}

int main()
{
    int groups = 0;
    cin >> groups;
    for (int i = 0; i<groups; ++i)
    {
        vector<vector<int>> datas;
        int planes = 0;
        cin >> planes;
        for (int p = 0; p<planes; ++p)
        {
            int s, d, e;
            cin >> s >> d >> e;
            datas.push_back({s, d, e});
        }
        if (judge(datas))
        {
            cout << "YES\n";
        } else
        {
            cout << "NO\n";
        }

    }
    return 0;
}
