#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int cnt = 0;
    int target = -1;
    cin >> cnt >> target;

    vector<int> nums;
    for(int i = 0; i < cnt ; ++i)
    {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }

    nums.erase(remove(nums.begin(), nums.end(), target), nums.end());

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