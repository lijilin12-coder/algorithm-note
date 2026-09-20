#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 2500010;

struct Sum {
    int s, c, d;
}sum[N];

int n, m;

int main()
{
    cin >> n;
    for (int c = 0; c*c <=n; c++)
        for(int d = c; c*c + d * d <=n; d ++) 
            sum[m ++] = {c*c + d*d, c, d};
    sort(sum, sum+m, [&](Sum& a, Sum& b){
        if (a.s != b.s) return a.s < b.s;
        if (a.c != b.c) return a.c < b.c;
        return a.d < b.d;
    });
    
    for (int a = 0; a*a <=n; a++)
        for (int b = 0; a*a + b*b <=n; b ++)
        {
            int t = n - a*a - b*b;
            int l = 0, r = m -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                // 求左边界
                if (sum[mid].s == t) 
                {
                    r = mid-1;
                } else if (sum[mid].s < t)
                {
                    l = mid + 1;
                } else if (sum[mid].s > t) 
                {
                    r = mid - 1;
                }
            }
            if (sum[l].s == t) {
                printf("%d %d %d %d\n",a, b, sum[l].c, sum[l].d);
                return 0;
            }
        }
    
    
    return 0;
}