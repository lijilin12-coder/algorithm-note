#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] == b[0] ? b[1] < a[1] : a[0] < b[0];
        });

        // 对高度数组寻找LIS
        vector<int> hight;
        for(auto& item : envelopes) {
            hight.push_back(item[1]);
        }
        return lengthOfLIS(hight);
    }

    int lengthOfLIS(vector<int>& nums) 
    {
        vector<int> top(nums.size());
        // 牌堆数初始化为 0
        int piles = 0;
        for (int i = 0; i < nums.size(); i++) {
            // 要处理的扑克牌
            int poker = nums[i];

            // ***** 搜索左侧边界的二分查找 *****
            int left = 0, right = piles-1;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (top[mid] >= poker) {
                    right = mid-1;
                } else if (top[mid] < poker) {
                    left = mid + 1;
                }
            }
            // ********************************
            
            // 没找到合适的牌堆，新建一堆
            if (left == piles) piles++;
            // 把这张牌放到牌堆顶
            top[left] = poker;
        }
        // 牌堆数就是 LIS 长度
        return piles;
    }
};

int main() {
    int n;
    cin >> n;

    vector<vector<int>> envelopes(n, vector<int>(2));
    for (int i = 0; i < n; ++i)
        cin >> envelopes[i][0] >> envelopes[i][1];

    Solution sol;
    cout << sol.maxEnvelopes(envelopes) << '\n';
    return 0;
}
