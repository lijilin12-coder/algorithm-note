#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int longestWPI(vector<int>& hours) {
       
        return 0;
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> hours(n);
    for (int i = 0; i < n; ++i)
        cin >> hours[i];

    Solution sol;
    cout << sol.longestWPI(hours) << '\n';
    return 0;
}
