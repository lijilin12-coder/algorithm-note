// 提示：用 while (cin >> x) 把数据读入 vector，再用 sort(v.begin(), v.end()) 排序后输出。
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int x;
    vector<int> nums;
    while(cin >> x)
    {
        nums.push_back(x);
    }

    sort(nums.begin(), nums.end());

    bool first = true;
    for(auto item : nums)
    {
        if (first)
        {
            cout << item;
            first = false;
        } else
        {
            cout << " " << item;
        }
    }
    cout << endl;
    return 0;
}