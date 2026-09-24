#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        int res = 0;
        string ans = "";
        for(int f = 0; f<n; ++f)
        {
            for(int l = n-1; l > f; --l)  {
                if (s[f] == s[l]) {
                    int cur_len = get_len(s, f, l);
                    if ( cur_len > res)
                    {
                        res = cur_len;
                        ans = s.substr(f, l);
                    }
                }
            }
        }
        return ans;
    }
    int get_len(const string str, int s, int e)
    {
        int res = 0;
        while(s<=e)
        {
            if (str[s] != str[e])
            {
                return -1;
            }
            s++;
            e--;
        }
        return e - s + 1;
    }
};

int main() {
    string s;
    cin >> s;

    Solution sol;
    cout << sol.longestPalindrome(s) << '\n';
    return 0;
}
