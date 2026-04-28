#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 20, MAXV = 200, INF = 0x3f3f3f3f;
char board1[MAXN + 1][MAXN + 1], board2[MAXN + 1][MAXN + 1];
bool vis[MAXN][MAXV + 1][MAXV + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> board1[i];
  for (int i = 0; i < N; ++i) cin >> board2[i];

  queue<tuple<int, int, int>> q;
  q.emplace(0, 0, 0); vis[0][0][0] = true;
  while (!q.empty()) {
    auto [v, x, y] = q.front(); q.pop();
    for (int u = 0; u < N; ++u) {
      if (board1[u][v] == '.') continue;
      int nx = x + (board1[u][v] - '0'), ny = y + (board2[u][v] - '0');
      if (nx > MAXV || ny > MAXV || vis[u][nx][ny]) continue;
      q.emplace(u, nx, ny); vis[u][nx][ny] = true;
    }
  }

  int ans = INF;
  for (int x = 0; x <= MAXV; ++x) for (int y = 0; y <= MAXV; ++y) {
    if (vis[1][x][y]) ans = min(ans, x * y);
  }
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
