#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXC = 25, MAXT = 1000, INF = 1e18;
int E[MAXC + 1][MAXT + 1], P[MAXC + 1][MAXT + 1];
ll dp[MAXC + 1][MAXT + 1];

void solve() {
  int C, T, L; cin >> C >> T >> L;
  for (int i = 1; i <= C; ++i) for (int j = 1; j <= T; ++j) {
    cin >> P[i][j] >> E[i][j];
    dp[i][j] = INF;
  }

  for (int j = 1; j <= T; ++j) dp[1][j] = P[1][j] + E[1][j];
  for (int i = 2; i <= C; ++i) for (int pt = 1; pt <= T; ++pt) for (int ct = 1; ct <= T; ++ct) {
    int dist = abs(P[i][ct] - P[i - 1][pt]);
    dp[i][ct] = min(dp[i][ct], dp[i - 1][pt] + dist + E[i][ct]);
  }

  ll ans = INF;
  for (int j = 1; j <= T; ++j) ans = min(ans, dp[C][j] + abs(P[C][j] - L));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
