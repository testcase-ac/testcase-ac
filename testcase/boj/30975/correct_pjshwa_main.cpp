#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 14, INF = 0x3f3f3f3f;
int P[MAXN], dp[1 << MAXN][MAXN];
int S[MAXN], E[MAXN], W[MAXN][MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> P[i], --P[i];

  memset(W, 0x3f, sizeof(W));
  for (int i = 0; i < N; ++i) S[i] = E[i] = INF;

  for (int i = 0; i < M; ++i) {
    int u, v, w; cin >> u >> v >> w;
    --u; --v;

    if (u == N) S[v] = min(S[v], w);
    else if (v == N) E[u] = min(E[u], w);
    else W[u][v] = min(W[u][v], w);
  }

  memset(dp, 0x3f, sizeof(dp));
  for (int i = 0; i < N; ++i) {
    if (P[i] == i) dp[1 << i][i] = S[i];
  }

  for (int s = 1; s < (1 << N); ++s) {
    for (int i = 0; i < N; ++i) {
      if (!(s & (1 << i))) continue;
      if (!(s & (1 << P[i]))) continue;

      for (int j = 0; j < N; ++j) {
        if (!(s & (1 << j))) continue;
        dp[s][i] = min(dp[s][i], dp[s ^ (1 << i)][j] + W[j][i]);
      }
    }
  }

  int ans = INF;
  for (int i = 0; i < N; ++i) ans = min(ans, dp[(1 << N) - 1][i] + E[i]);
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
