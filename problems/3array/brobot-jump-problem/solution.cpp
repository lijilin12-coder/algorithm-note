//
#include <iostream>
#include <vector>

using namespace std;
const int MAX_N = 10e5;
int H[MAX_N + 1];

bool jump(int n, int E) {
  if (n > MAX_N)
    return false;
  for (int k = 0; k < n; ++k) {
    if (H[k] > E) {
      E -= H[k] - E;
    } else {
      E += E - H[k];
    }
    if (E < 0)
      return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> H[i];
  }
  /*
    for (int E = 0; E <= MAX_N; ++E) {
      if (jump(n, E)) {
        cout << E << endl;
        return 0;
      }
    }
  */
  // Binery Search
  int l = 0, r = MAX_N;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (jump(n, m)) {
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  cout << l << endl;
  return 0;
}
