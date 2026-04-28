#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 400, MAXT = 200, BIAS = 200, MOD = 1e9 + 7;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int dp[MAXT + 1][MAXN + 1][MAXN + 1], O[MAXN + 1][MAXN + 1];

void solve() {
  int Xs, Ys, T, Xh, Yh, N; cin >> Xs >> Ys >> T >> Xh >> Yh >> N;

  Xh -= Xs, Yh -= Ys;
  if (abs(Xh) + abs(Yh) > T) return cout << "0\n", void();

  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    x -= Xs, y -= Ys;
    if (abs(x) + abs(y) <= T) O[x + BIAS][y + BIAS] = 1;
  }

  dp[0][BIAS][BIAS] = 1; int ans = 0;
  for (int t = 0; t < T; ++t) {
    ans = (ans + dp[t][Xh + BIAS][Yh + BIAS]) % MOD;

    for (int x = 0; x <= MAXN; ++x) for (int y = 0; y <= MAXN; ++y) {
      if (x == Xh + BIAS && y == Yh + BIAS) continue;
      for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx > MAXN || ny < 0 || ny > MAXN) continue;
        if (O[nx][ny]) continue;

        dp[t + 1][nx][ny] = (dp[t + 1][nx][ny] + dp[t][x][y]) % MOD;
      }
    }
  }
  ans = (ans + dp[T][Xh + BIAS][Yh + BIAS]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
