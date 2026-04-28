#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, INF = 0x3f3f3f3f;
int S[MAXN + 1][MAXN + 1], D[MAXN + 1];
int dp[MAXN][MAXN + 1], N, T;

int rec(int i, int t) {
  if (i == N) return t == 0 ? 0 : -INF;
  if (dp[i][t] != -1) return dp[i][t];

  int ret = 0;
  for (int u = 0; u <= t; ++u) {
    ret = max(ret, rec(i + 1, t - u) + S[i][u]);
  }
  return dp[i][t] = ret;
}

void solve() {
  cin >> N >> T;
  for (int i = 0; i < N; ++i) for (int t = 0; t <= T; ++t) cin >> S[i][t];
  for (int t = 0; t <= T; ++t) cin >> D[t];

  int ans = -INF;
  for (int t = 0; t <= T; ++t) {
    // t마다 냅색으로 최적시간 구하기

    memset(dp, -1, sizeof(dp));
    ans = max(ans, rec(0, t) - D[t]);
  }
  cout << ans << '\n';

  // 정답 역추적
  for (int ot = 0; ot <= T; ++ot) {
    memset(dp, -1, sizeof(dp));
    if (ans != rec(0, ot) - D[ot]) continue;

    int t = ot, val = ans + D[ot];
    for (int i = 0; i < N - 1; ++i) for (int u = 0; u <= t; ++u) {
      if (dp[i + 1][t - u] == -1) continue;
      if (val != dp[i + 1][t - u] + S[i][u]) continue;

      cout << u << ' ';
      t -= u, val -= S[i][u];
      break;
    }

    cout << t << '\n';
    break;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
