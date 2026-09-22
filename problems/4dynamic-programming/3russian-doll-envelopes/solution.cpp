#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        
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
