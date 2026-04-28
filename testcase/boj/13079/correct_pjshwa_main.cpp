#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 30;
ll dp[MAXN + 1];

void solve() {
  int n, m, k; cin >> n >> m >> k;
  dp[0] = 1;
  for (int i = 1; i <= n; ++i) {
    dp[i] = 0;
    for (int a = 1; a <= i; ++a) {
      if (a % k == m) continue;
      dp[i] += dp[i - a];
    }
  }
  cout << dp[n] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
