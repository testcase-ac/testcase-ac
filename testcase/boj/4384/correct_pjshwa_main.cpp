#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MW = 45'000;
int val[101], n;
bool dp[51][MW + 1];

int main() {
  fast_io();

  int n, s = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> val[i];
    s += val[i];
  }

  dp[0][0] = true;
  for (int ai = 1; ai <= n; ai++) {
    for (int ci = min(ai, n / 2); ci >= 1; ci--) {
      for (int cw = 0; cw <= MW; cw++) {
        if (dp[ci - 1][cw]) dp[ci][cw + val[ai]] = true;
      }
    }
  }

  int md = 2e9, mw = -1;
  for (int cw = 0; cw <= MW; cw++) {
    if (dp[n / 2][cw] && cw < s) {
      int rw = s - cw;
      if (md > abs(rw - cw)) {
        mw = cw;
        md = abs(rw - cw);
      }
    }
  }

  cout << min(mw, s - mw) << ' ' << max(mw, s - mw);
}
