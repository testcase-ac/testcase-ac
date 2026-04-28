#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool ns_eligible(string& U, int ps, int ns, int M) {
  for (int j = 0; j < M; ++j) {
    if (!(ns & (1 << j))) continue;

    if (U[j] == 'w') return false;
    if (ps & (1 << j)) return false;
    if (j > 0 && (ns & (1 << (j - 1)))) return false;
  }
  return true;
}

void solve() {
  int N, M; string U; cin >> N >> M >> U >> M >> N;

  vector<string> B(N + 1);
  for (int i = 1; i <= N; ++i) cin >> B[i];

  vector<vector<int>> dp(N + 1, vector<int>(1 << M)); int ans = 0;
  for (int i = 1; i <= N; ++i) {
    for (int ps = 0; ps < (1 << M); ++ps) {
      for (int ns = 0; ns < (1 << M); ++ns) {
        if (!ns_eligible(B[i], ps, ns, M)) continue;

        dp[i][ns] = max(dp[i][ns], dp[i - 1][ps] + __builtin_popcount(ns));
        ans = max(ans, dp[i][ns]);
      }
    }
  }

  auto P = B; int cs;
  for (cs = 0; dp[N][cs] != ans; ++cs);
  for (int j = 0; j < M; ++j) {
    if (cs & (1 << j)) P[N][j] = 'O';
  }

  for (int i = N; i >= 2; --i) {
    for (int ps = 0; ps < (1 << M); ++ps) {
      if (!ns_eligible(B[i], ps, cs, M)) continue;
      if (dp[i][cs] != dp[i - 1][ps] + __builtin_popcount(cs)) continue;

      cs = ps;
      break;
    }

    for (int j = 0; j < M; ++j) {
      if (cs & (1 << j)) P[i - 1][j] = 'O';
    }
  }

  for (int i = 1; i <= N; ++i) cout << P[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
