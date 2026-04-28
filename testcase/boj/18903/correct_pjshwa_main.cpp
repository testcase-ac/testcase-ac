#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e6 + 3;

void solve() {
  int n, k, r; cin >> n >> k >> r;

  vector<int> T(r);
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    ++T[x % r];
  }
  for (int i = 0; i < r; ++i) T[i] = min(T[i], k);

  vector<vector<int>> dp(r, vector<int>(k + 1));
  for (int j = 0; j <= T[0]; ++j) dp[0][j] = 1;

  for (int i = 1; i < r; ++i) f
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
