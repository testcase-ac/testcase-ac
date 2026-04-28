#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
ld C[MAX + 1], dp[MAX + 1];

void solve() {
  ll c, t, r; ld p; cin >> c >> t >> r >> p;

  // time takes to write consecutive i chars without saving
  C[0] = 0;
  for (int i = 1; i <= c; ++i) {
    C[i] = (C[i - 1] + 1 + p * r) / (1 - p);
  }

  // time takes to write consecutive i chars with saving
  dp[0] = 0;
  for (int i = 1; i <= c; ++i) {
    dp[i] = C[i];
    for (int j = 0; j < i; ++j) {
      dp[i] = min(dp[i], dp[j] + C[i - j] + t);
    }
  }

  cout << fixed << setprecision(10) << dp[c] + t << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
