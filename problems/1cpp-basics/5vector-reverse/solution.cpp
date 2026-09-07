// 提示：用 vector<int> 读入 n 个数，调用 reverse(v.begin(), v.end()) 反转后输出。
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int cnt = 0;
    cin >> cnt;

    vector<int> nums;
    for(int i = 0; i < cnt ; ++i)
    {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }

    reverse(nums.begin(), nums.end());

    bool first = true;
    for(auto x : nums)
    {
        if (first)
        {
            cout << x;
            first = false;
        } else
        {
            cout << " " << x ;
        }
    }
    cout << endl;

    return 0;
}