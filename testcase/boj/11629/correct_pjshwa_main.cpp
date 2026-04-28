#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, MOD = 5318008;
const int dx[] = {1, 0, -1};
int dp[2][MAXN + 1];

void solve() {
  int N, X1, Y1, X2, Y2; cin >> N >> X1 >> Y1 >> X2 >> Y2;
  int xd = abs(X1 - X2), yd = abs(Y1 - Y2);
  if (xd > yd) swap(xd, yd), swap(X1, Y1), swap(X2, Y2);

  for (int i = 0; i < 2; ++i) fill(dp[i], dp[i] + N + 1, 0);
  int moves = yd; dp[0][X1] = 1;
  for (int i = 1; i <= moves; ++i) for (int x = 1; x <= N; ++x) {
    dp[i & 1][x] = 0;
    for (int j = 0; j < 3; ++j) {
      int px = x + dx[j];
      if (px < 1 || px > N) continue;
      dp[i & 1][x] = (dp[i & 1][x] + dp[~i & 1][px]) % MOD;
    }
  }
  cout << dp[moves & 1][X2] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
