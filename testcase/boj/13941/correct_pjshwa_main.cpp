#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 20, INF = 0x3f3f3f3f;
int C[MAX][MAX], dp[1 << MAX];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> C[i][j];

  memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;

  int ans = INF;
  for (int state = 0; state < (1 << N); ++state) {

    for (int src = 0; src < N; ++src) {
      if (state & (1 << src)) continue;

      for (int dst = 0; dst < N; ++dst) {
        if (src == dst) continue;
        if (state & (1 << dst)) continue;

        dp[state | (1 << src)] = min(dp[state | (1 << src)], dp[state] + C[src][dst]);
      }
    }

    int cnt = __builtin_popcount(state);
    if (cnt == N - K) ans = min(ans, dp[state]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
