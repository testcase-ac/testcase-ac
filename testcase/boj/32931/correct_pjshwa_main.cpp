#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 2e5, INF = 1e18;
ll A[2][MAXN], dp[3][MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < 2; ++i) for (int j = 0; j < N; ++j) cin >> A[i][j];
  for (int i = 0; i < 3; ++i) for (int j = 0; j < N; ++j) dp[i][j] = -INF;

  dp[0][0] = A[0][0]; dp[2][0] = A[0][0] + A[1][0];
  for (int j = 1; j < N; ++j) {
    for (int s = 0; s < 3; ++s) {
      ll val;
      if (s == 0) val = A[0][j];
      if (s == 1) val = A[1][j];
      if (s == 2) val = A[0][j] + A[1][j];

      for (int ps = 0; ps < 3; ++ps) {
        if (s == 0 && ps == 1) continue;
        if (s == 1 && ps == 0) continue;
        dp[s][j] = max(dp[s][j], dp[ps][j - 1] + val);
      }
    }
  }

  cout << max(dp[1][N - 1], dp[2][N - 1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
