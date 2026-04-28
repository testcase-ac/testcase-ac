#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500, INF = 0x3f3f3f3f;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int O[MAXN + 1][MAXN + 1], cdist[MAXN + 1][MAXN + 1];

void solve() {
  int N, M, A, B, K; cin >> N >> M >> A >> B >> K;
  while (K--) {
    int x, y; cin >> x >> y;
    O[x][y] = 1;
  }

  // prefix sum for O
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) {
    O[i][j] += O[i - 1][j] + O[i][j - 1] - O[i - 1][j - 1];
  }

  auto oob = [&](int x, int y) {
    return x < 1 || x + A - 1 > N || y < 1 || y + B - 1 > M;
  };
  auto movable = [&](int x, int y) {
    if (oob(x, y)) return false;
    int cnt = O[x + A - 1][y + B - 1] - O[x - 1][y + B - 1] - O[x + A - 1][y - 1] + O[x - 1][y - 1];
    return cnt == 0;
  };

  int sx, sy, ex, ey; cin >> sx >> sy >> ex >> ey;
  memset(cdist, 0x3f, sizeof(cdist));
  queue<pii> q;
  q.emplace(sx, sy); cdist[sx][sy] = 0;

  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    if (x == ex && y == ey) break;

    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d], ny = y + dy[d];
      if (movable(nx, ny) && cdist[nx][ny] > cdist[x][y] + 1) {
        cdist[nx][ny] = cdist[x][y] + 1;
        q.emplace(nx, ny);
      }
    }
  }

  int ans = cdist[ex][ey];
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
