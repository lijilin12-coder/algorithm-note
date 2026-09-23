#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        mem = vector<vector<string>>(s.size()+1);
        dp(s, wordDict, "");
        return probe_ans;
    }
    vector<vector<string>> mem;
    vector<string> probe_ans;
    void dp(string& s, vector<string>& wordDict, string cur_ans, vector<vector<string>>& cur_mem)
    {
        if (s.empty()) {
            probe_ans.push_back(cur_ans);
            return;
        }
        if (!mem[s.size()].empty()) {
            for(const auto& item : mem[s.size()]) {
                if (cur_ans.empty()){
                    cur_ans+= item;
                } else {
                    cur_ans+= " " + item;
                }
            }
            probe_ans.push_back(cur_ans);
            cout << "Cache hit " << s;
            return;
        }

        for(const auto& w : wordDict)
        {
            string cur_ans_t = cur_ans;
            auto it = s.find(w);
            if (it == string::npos) continue;
            if (it != 0) continue;
            auto subs = s.substr(w.size(), s.length()-w.size());
            if (!cur_ans_t.empty()) {
                cur_ans_t= cur_ans_t+ " " + w;
            } else {
                cur_ans_t+= w;
            }
            if(subs.empty() {
                mem[s.size()] = 
            })
            dp(subs, wordDict, cur_ans_t);
        }
        return 

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
    vector<string> res = sol.wordBreak(s, wordDict);

    cout << res.size() << "\n";
    for (auto& sentence : res)
        cout << sentence << "\n";
    return 0;
}
