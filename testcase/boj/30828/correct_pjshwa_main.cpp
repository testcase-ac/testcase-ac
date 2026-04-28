#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
int T[MAXN + 1];
int dp[MAXN + 1][MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> T[i];

  for (int i = 1; i <= N; ++i) {
    vector<vector<int>> d(N + 1, vector<int>(512, -1));
    d[i][0] = 0; d[i][T[i]] = 1;
    dp[i][i] = T[i] + 1;

    for (int j = i + 1; j <= N; ++j) {
      for (int v = 0; v < 512; ++v) d[j][v] = d[j - 1][v];
      for (int v = 0; v < 512; ++v) {
        if (d[j - 1][v] == -1) continue;

        int nv = v ^ T[j];
        d[j][nv] = max(d[j][nv], d[j - 1][v] + 1);
      }
      for (int v = 0; v < 512; ++v) {
        if (d[j][v] == -1) continue;
        dp[i][j] = max(dp[i][j], v + d[j][v]);
      }
    }
  }

  int Q; cin >> Q;
  while (Q--) {
    int l, r; cin >> l >> r;
    cout << dp[l][r] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
