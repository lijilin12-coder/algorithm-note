#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minimumDeleteSum(string word1, string word2) {
        /*
            sea  | eat

             Case1 :  delete w1  --> dp(w1, i1+11, w2, i2);
             Case2 :  delete w2  --> dp(w1, i1,w2,i2+1);
        */

        return dp(word1, 0, word2, 0);
    }

    int mem[510][510];
    int dp(string& w1, int i1, string& w2, int i2)
    {
        // bad case
        if (i1 == w1.size()) {
            int ascii_sum = 0;
            for(char c:w2) {
                ascii_sum+= int(c);
            }
            return ascii_sum;
        }

        if (i2 == w2.size())
        {
            int ascii_sum = 0;
            for(char c:w1) {
                ascii_sum+= int(c);
            }
            return ascii_sum;
        }

        if (w1 == w2) return 0;
        if (mem[i1][i2] != 0) return mem[i1][i2];
        int res = -1;
        if (w1[i1] == w2[i2])
        {
            res = dp(w1, i1+1, w2, i2+1);
        }  else
        {
            res = min(dp(w1, i1+1, w2, i2) + int(w1[i1]), dp(w1, i1, w2, i2+1)+int(w2[i2]));
        }
        mem[i1][i2] = res;
        return res;
    }
};

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    Solution sol;
    cout << sol.minimumDeleteSum(s1, s2) << '\n';
    return 0;
}
