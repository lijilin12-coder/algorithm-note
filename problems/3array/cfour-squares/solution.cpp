#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;
vector<int> get_ans(int n) {
    unordered_map<int, int> sqrt_idx;
    sqrt_idx[0] = 0;
    int sqr = sqrt(n);
    for (int i1 = 0; i1 < sqr ; ++i1) {
        for (int i2 = 0; i2 < n - i1*i1; ++i2) {
            for (int i3 = 0; i3 < n-i1*i1-i2*i2; ++i3) {
                int need = n - i1*i1 - i2*i2 - i3*i3;
                if (sqrt_idx.count(need)) {
                    return {i1, i2, i3, sqrt_idx[need]};
                }
                // 二分查找 i4*i4 = need
                int l = 0;
                int r = sqrt(need) + 1;
                while (l <= r) {
                    int m = l + (r - l) / 2;
                    int ms = m * m;
                    if(ms == need) {
                        return {i1, i2, i3, ms};
                    } else if (ms < need) {
                        l = m + 1;
                    } else if (ms > need) {
                        r = m - 1;
                    }
                    sqrt_idx[ms] = m;
                }
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    auto ans = get_ans(n);
    printf("%d %d %d %d\n", ans[0], ans[1], ans[2], ans[3]);

    return 0;
}