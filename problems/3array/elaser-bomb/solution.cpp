#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAX_L = 5000;
int pre_sum[MAX_L+1][MAX_L+1];
struct LWData {
    int x;
    int y;
    int w;

    bool operator<(const LWData& a){
        if ( x < a.x) {
            return true;
        }  else if (a.x == x) {
            return y<a.y  ;
        } else if ( x > a.x) {
            return false;
        }
        return false;
    }
};

int get_pre_sum(int r1, int c1, int r2, int c2, int max_r, int max_c) {

    r2 = min(r2, max_r);
    c2 = min(c2, max_c);
    int rst = pre_sum[r2 + 1] [c2 + 1] - pre_sum[r2 + 1] [c1] 
            - pre_sum[r1][c2+1] + pre_sum[r1][c2];
    return rst;

}

int main()
{
    memset(pre_sum, 0, sizeof pre_sum);
    int N, r;
    map<LWData, int> coord_w;
    cin >> N >> r;
    int max_x = 0, max_y = 0;
    for(int i = 0; i<N; i++) {
        LWData d;
        cin >> d.x >> d.y >> d.w;
        coord_w.insert({d, d.w});
        max_x = max(max_x, d.x);
        max_y = max(max_y, d.y);
    }


    for(int row = 0; row <= max_y; ++ row) {
        for (int col = 0; col <= max_x; ++col) {
            LWData d;
            d.x = col;
            d.y = row;
            int v = 0;
            if (coord_w.count(d)) {
                v = coord_w[d];
            }
            pre_sum[row+1][col+1] = v+pre_sum[row+1][col] + pre_sum[row][col+1] - pre_sum[row][col];
        }
    }

    int max_v = 0;
    for(int row = 0; row <= max_y; ++ row) {
        for (int col = 0; col <= max_x; ++col) {
            int cur_max = get_pre_sum(row, col, row+r-1, col+r-1, max_y, max_x);
            max_v = max(max_v, cur_max);
        }
    }
    cout << max_v << endl;
    
    return 0;
}