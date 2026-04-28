#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

int c;
void solve() {
  int n; cin >> n;
  vector<vector<int>> U(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; ++i) for (int j = i; j <= n; ++j) cin >> U[i][j];

  vector<ll> dp(n + 1, INF); dp[0] = 0;
  for (int j = 1; j <= n; ++j) for (int i = 1; i <= j; ++i) {
    dp[j] = min(dp[j], dp[i - 1] + U[i][j] + c);
  }
  cout << dp[n] << '\n';
}

int main() {
  fast_io();

  while (cin >> c) solve();
}
