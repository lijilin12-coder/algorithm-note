#include <csetjmp>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
  4 5 0 -2 -3 1
0 4 9 9  7  4 5
1 4 4 4  2  4 0

{{5}, {0}, {5, 0}, {5, 0, -2 , -3}, {0, -2, -3}, {-2, -3}, {4, 5, 0, -2,-3, 1}}
ans 1
{
  4:3
}

1. nums[i] % k == 0
2. nums[i]
{
    0 :1
    4: 3
    2: 1





}





void dfs(int i )
{
    if (i==n)  return ;
    if check(cur_ans) == true : ans++;

    // PICK | NOT PICK
    if (cur_ans.empty() || cur_ans[cur_ans.size()-1] +1 == i){
        visited[i] = true;
        cur_ans.push_back(i);
        dfs(i+1);
        visited[i] = false;
    }
    cur_ans.pop_back();

    dfs(i+1);

}
*/

class Solution {
public:
  const static int N = 3 * 10e4;
  int presum[N + 1];
  int subarraysDivByK(vector<int> &nums, int k) {
    // 在这里实现你的代码
    for (int i = 0; i < k; i++)
      presum[i + 1] = nums[i] + presum[i];

    int mod_rst[k];
    memset(mod_rst, 0, sizeof mod_rst);
    memset(presum, 0, sizeof presum);
    mod_rst[0] = 1;
    int ans = 0;
    for (int i = 1; i <= k; ++i) {
      int m = presum[i] % k;
      if (mod_rst[m] != 0) {
        ans += mod_rst[m];
        mod_rst[m]++;
      }
    }

    return ans;
  }
};

int main() {
  int n, k;
  cin >> n >> k;

  vector<int> nums(n);
  for (int i = 0; i < n; ++i)
    cin >> nums[i];

  Solution sol;
  cout << sol.subarraysDivByK(nums, k) << '\n';
  return 0;
}
