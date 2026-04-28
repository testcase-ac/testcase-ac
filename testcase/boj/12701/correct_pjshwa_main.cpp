#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MOD = 10007;
const int dx[2] = {-1, -2}, dy[2] = {-2, -1};
int B[MAXN][MAXN], dp[MAXN][MAXN];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int H, W, R; cin >> H >> W >> R;
  for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) {
    B[i][j] = dp[i][j] = 0;
  }
  while (R--) {
    int r, c; cin >> r >> c;
    B[r - 1][c - 1] = 1;
  }

  dp[0][0] = 1;
  for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) {
    if (B[i][j]) continue;
    for (int k = 0; k < 2; ++k) {
      int pi = i + dx[k], pj = j + dy[k];
      if (pi < 0 || pj < 0) continue;
      dp[i][j] = (dp[i][j] + dp[pi][pj]) % MOD;
    }
  }
  cout << dp[H - 1][W - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
