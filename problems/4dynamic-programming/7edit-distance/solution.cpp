#include <iostream>
#include <string>
#include <climits>
#include <vector>
using namespace std;
typedef struct Node {
    int r,c,v;
    Node(int _r, int _c, int _v): r(_r), c(_c), v(_v)
    {

    }
    bool operator==(const Node& a)
    {
        return r == a.r && c == a.c;
    }
}Node;


class Solution {
public:
    int minDistance(string word1, string word2) {
        /*
        sword1|word2
            3种状态
                1. 删除   -- >  word1   | word2
                2. 替换   -- >  wword1  | word2
                3. 插入   -- >  wsword1 | word2

        dp
        -1|-1
        s|w
        3种状态
                1. 删除   -- >  
                    1.1 _   | w
                    1.2 
                2. 替换   -- >  wword1  | word2

                3. 插入   -- >  wsword1 | word2

        
        */
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp = vector<vector<int>>(m+1, vector<int>(n+1)); 
        for(int c1=1; c1<=word2.size(); c1++) 
        {
            dp[0][c1] = c1;
        }
        
        for(int r1 = 1; r1 <=word1.size(); r1++)
        {
            dp[r1][0] = r1;
        }
        
        Node last_print = {0,0,0};
        for(int i1 = 1; i1<=word1.size();i1++)
        {
            for(int i2 = 1; i2 <= word2.size();i2++)
            {
                if (word1[i1 - 1] == word2[i2 - 1]){
                    dp[i1][i2] = dp[i1 - 1][i2 - 1];
                    if ( Node(i1-1, i2-1, 0) == last_print)
                    {
                        last_print = Node(i1, i2, 0);
                        cout << "Ignore \n";
                    }
                }

                else{
                    int repl_step = dp[i1-1][i2-1] + 1;
                    int remv_step = dp[i1][i2-1] + 1;
                    int inst_step = dp[i1-1][i2] + 1;
                    int rst= min(
                        repl_step, min(
                            remv_step, inst_step
                        ) 
                    );
                    dp[i1][i2] = rst;
                    if (rst == repl_step && Node(i1-1, i2-1,1)==last_print){
                        last_print = Node(i1, i2,1);
                        cout<< "replace\n";
                    }
                    else if (rst == remv_step && Node(i1, i2-1,2) == last_print) {
                        last_print = Node(i1, i2,2);
                        cout << "Remove\n";
                    }
                    else if (rst == inst_step && Node(i1-1, i2,2) == last_print) {
                        last_print = Node(i1, i2,3);
                        cout << "Insert \n";
                    }
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }

    
};

int main() {
    string word1, word2;
    cin >> word1 >> word2;

    Solution sol;
    cout << sol.minDistance(word1, word2) << '\n';
    return 0;
}
