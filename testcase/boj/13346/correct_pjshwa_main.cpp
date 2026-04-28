#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 100;
ll dp[MAX][2 * MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int q, n, d;
  cin >> q >> n >> d;

  string s, t;
  cin >> s >> t;

  if (s[0] == t[0]) {
    dp[0][0] = 1;
    dp[0][2] = q - 1;
  }
  else {
    dp[0][1] = 2;
    dp[0][2] = q - 2;
  }

  for (int i = 1; i < n; i++) {
    for (int di = 200; di >= 0; di--) {
      if (s[i] == t[i]) {
        ll cur = 0;
        cur += dp[i - 1][di];
        if (di > 1) cur += dp[i - 1][di - 2] * (q - 1);
        dp[i][di] = cur;
      }
      else {
        ll cur = 0;
        if (di > 0) cur += dp[i - 1][di - 1] * 2;
        if (di > 1) cur += dp[i - 1][di - 2] * (q - 2);
        dp[i][di] = cur;
      }
    }
  }

  cout << dp[n - 1][d] << '\n';
}
