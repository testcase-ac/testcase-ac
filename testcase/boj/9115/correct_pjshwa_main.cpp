#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1.5e6;
bool dp[MAX + 1];

void solve() {
  memset(dp, 0, sizeof(dp));

  int a, b, c, d;
  cin >> a >> b >> c >> d;

  dp[0] = true;
  int cnt = 0, cmax = 0;
  for (int i = 1; i <= MAX; i++) {
    if (i >= a) dp[i] |= dp[i - a];
    if (i >= b) dp[i] |= dp[i - b];
    if (i >= c) dp[i] |= dp[i - c];
    if (i >= d) dp[i] |= dp[i - d];

    if (!dp[i]) {
      if (i <= 1e6) cnt++;
      cmax = i;
    }
  }

  cout << cnt << '\n';
  cout << (cmax <= 1e6 ? cmax : -1) << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
