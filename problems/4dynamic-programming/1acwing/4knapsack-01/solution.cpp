#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_L = 1010;
int w[MAX_L],v[MAX_L];
int mem[MAX_L][MAX_L];


/**
 * Max total value choosing from the first idx items, total volume <= v.
 * @param idx  consider only items 1..idx
 * @param vol  volume limit
 * @return     the max total value
 */
int dfs(int idx, int vol)
{
    if (idx == 0) return 0;
    if (mem[idx][vol] != 0) return mem[idx][vol];
    //Select state: SELECT | NOT SELET
    int collect_weight = dfs(idx-1, vol);
    if (vol >= v[idx]){
        collect_weight = max(
            collect_weight, dfs(idx-1, vol-v[idx]) + w[idx]
        );
    }
    mem[idx][vol] = collect_weight;
    return mem[idx][vol];
}

int f[MAX_L][MAX_L];
int dp(int max_idx, int max_vol)
{
    for(int idx = 1; idx <= max_idx; ++ idx)
    {
        for(int vol = 1; vol<=max_vol; ++ vol)
        {
            f[idx][vol] = f[idx-1][vol];
            if (vol >= v[idx])
            {
                f[idx][vol] = max(
                    f[idx][vol], f[idx-1][vol-v[idx]] + w[idx]
                );
            }
        }
    }
    return f[max_idx][max_vol];
}


int main(int argc, char const *argv[])
{
    
    int N,V;
    cin >> N >> V;

    for(int i = 1;i<=N;i++)
    {
        cin >> v[i] >> w[i];
    }
    cout << dp(N, V) << endl;
    // cout << dfs(N, V) << endl;
    return 0;
}
