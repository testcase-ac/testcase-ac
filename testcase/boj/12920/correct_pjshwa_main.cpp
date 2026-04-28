#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int val[2000], wgt[2000];
int n, m, dp[2000][10001];

int main() {
  fast_io();

  int on, v, c, k;
  cin >> on >> m;

  n = 0;
  for (int i = 0; i < on; i++) {
    cin >> v >> c >> k;
    int ki = 1, ks = 0;
    while (1) {
      if (ks + ki > k) {
        if (k > ks) {
          val[n] = c * (k - ks);
          wgt[n] = v * (k - ks);
          n++;
        }
        break;
      }
      else {
        val[n] = c * ki;
        wgt[n] = v * ki;
        ks += ki;
        ki <<= 1;
        n++;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int l = 1; l <= m; l++) {
      if (wgt[i - 1] <= l) dp[i][l] = max(val[i - 1] + dp[i - 1][l - wgt[i - 1]], dp[i - 1][l]);
      else dp[i][l] = dp[i - 1][l];
    }
  }

  cout << dp[n][m];
}
