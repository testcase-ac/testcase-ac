#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50000, MAXM = 100, INF = 0x3f3f3f3f;
int dp[MAXN + 1][MAXM + 1];

void solve() {
  int N, M, A, B; cin >> N >> M >> A >> B;
  for (int i = 1; i <= N; ++i) fill(dp[i], dp[i] + M + 1, 0x3f3f3f3f);

  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    for (int pv = 0; pv <= M; ++pv) {
      int ext_a, ext_b, cx, nv = pv + x;

      // Case 1. Fill remaining time with dj talk & pass the music to next chunk
      ext_a = max(0, x - M), ext_b = M - pv;
      cx = min(x, M);
      dp[i][cx] = min(dp[i][cx], dp[i - 1][pv] + A * ext_a + B * ext_b);

      // Case 2. Fit the music in current chunk
      cx = min(M, nv), ext_a = max(0, nv - M);
      dp[i][cx] = min(dp[i][cx], dp[i - 1][pv] + A * ext_a);
    }

    // cout << "dp[" << i << "]: ";
    // for (int j = 0; j <= M; ++j) cout << (dp[i][j] == INF ? -1 : dp[i][j]) << ' ';
    // cout << '\n';
  }

  int ans = INF;
  for (int j = 0; j <= M; ++j) ans = min(ans, dp[N][j] + B * (M - j));
  cout << ans << '\n';
}

int main() {
  fast_io();

  memset(dp, 0x3f, sizeof(dp));
  dp[0][0] = 0;

  int t = 1;
  cin >> t;
  while (t--) solve();
}
