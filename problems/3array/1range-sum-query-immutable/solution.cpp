#include <iostream>
#include <vector>
using namespace std;

class NumArray {
public:
    NumArray(vector<int>& nums) {
        // 在这里实现你的代码（初始化时做预处理，例如构建前缀和数组）
    }

    int sumRange(int left, int right) {
        // 在这里实现你的代码
        return 0;
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    int q;
    cin >> q;

    NumArray obj(nums);
    while (q--) {
        int left, right;
        cin >> left >> right;
        cout << obj.sumRange(left, right) << '\n';
    }
    return 0;
}
