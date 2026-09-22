#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        ans = false;
        mem = vector<bool>(s.size()+1, true);
        dp(s, wordDict);
        return ans;
    }
    bool ans = false;
    vector<bool> mem;
    void dp(string& s, vector<string>& wordDict)
    {
        if (ans) return;
        if (s.empty()) {
            ans =  true;
            return;
        }
        if (mem[s.length()] == false) return;
        for(const auto& w : wordDict)
        {
            auto it = s.find(w);
            if (it == string::npos) continue;
            if (it != 0) continue;
            auto subs = s.substr(w.size(), s.length()-w.size());
            dp(subs, wordDict);
            mem[subs.length()] = false;
        }
    }

};

int main() {
    string s;
    cin >> s;

    int n;
    cin >> n;
    vector<string> wordDict(n);
    for (int i = 0; i < n; ++i)
        cin >> wordDict[i];

    Solution sol;
    cout << (sol.wordBreak(s, wordDict) ? "YES" : "NO") << '\n';
    return 0;
}
