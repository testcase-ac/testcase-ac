#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000, MOD = 1e9 + 7;
char board[MAX + 1][MAX + 1];
int d1[MAX + 1][MAX + 1], d2[MAX + 1][MAX + 1];

bool movable(int x1, int y1, int x2, int y2) {
  bool xmove = x2 == x1 + 1 && y2 == y1, ymove = y2 == y1 + 1 && x2 == x1;
  return xmove || ymove;
}

void solve() {
  int N, M, K; cin >> M >> N >> K;
  for (int i = 0; i < N; i++) cin >> board[i];

  d1[0][0] = d2[N - 1][M - 1] = 1;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == '1') continue;
    if (i > 0) d1[i][j] = (d1[i][j] + d1[i - 1][j]) % MOD;
    if (j > 0) d1[i][j] = (d1[i][j] + d1[i][j - 1]) % MOD;
  }
  for (int i = N - 1; i >= 0; i--) for (int j = M - 1; j >= 0; j--) {
    if (board[i][j] == '1') continue;
    if (i < N - 1) d2[i][j] = (d2[i][j] + d2[i + 1][j]) % MOD;
    if (j < M - 1) d2[i][j] = (d2[i][j] + d2[i][j + 1]) % MOD;
  }

  int ans = d1[N - 1][M - 1];
  while (K--) {
    int x1, y1, x2, y2; cin >> y1 >> x1 >> y2 >> x2;

    ll cur = 0;
    if (!movable(x1, y1, x2, y2)) cur = (cur + (ll)d1[x1][y1] * d2[x2][y2]) % MOD;
    if (!movable(x2, y2, x1, y1)) cur = (cur + (ll)d1[x2][y2] * d2[x1][y1]) % MOD;
    ans = (ans + cur) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
