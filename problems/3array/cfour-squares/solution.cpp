#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int N = 5 * 10e6;

vector<vector<int>> cdsum(N); // {c*c+d*d, c, d}

int main(int argc, char *argv[]) {
  int a, b, c, d;
  int n, m = 0;
  cin >> n;
  // 1 9
  // 2 1
  for (c = 0; c * c <= n; ++c) {
    for (d = c; d * d + c * c <= n; ++d) {
      // 1. c d c*c + d*d;
      cdsum[m++] = {c * c + d * d, c, d};
    }
  }

  sort(cdsum.begin(), cdsum.end(), [&](vector<int> &a, vector<int> &b) {
    if (a[0] != b[0])
      return a[0] < b[0];
    if (a[1] != b[1])
      return a[1] < b[1];
    return a[2] < b[2];
  });

  for (a = 0; a * a <= n; ++a) {
    for (b = a; a * a + b * b <= n; ++b) {
      // Binary Search
      int t = n - a * a - b * b;
      int l = 0, r = cdsum.size() - 1;
      while (l <= r) {
        int m = l + (r - l) / 2;
        if (cdsum[m][0] >= t) {
          r = m - 1;
        } else {
          l = m + 1;
        }
      }

      if (cdsum[l][0] == t) {
        printf("%d %d %d %d\n", a, b, cdsum[l][1], cdsum[l][2]);
        return 0;
      }
    }
  }
  /*
        for (c = b; a * a + b * b + c * c <= n;c++)
        {
          for (d = c; a * a + b * b + c * c + d * d <= n; ++d) {
            if (a * a + b * b + c * c + d * d == n) {
              printf("%d %d %d %d\n", a, b, c, d);
              return 0;
            }
          }
        }
  */
  return 0;
}
