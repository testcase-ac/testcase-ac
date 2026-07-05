#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int B[MAXN + 1][MAXN + 1], cdist[MAXN + 1][MAXN + 1];
pii from[MAXN + 1][MAXN + 1];

void solve() {
  int N, sx, sy, ex, ey, K, M; cin >> N >> sx >> sy >> ex >> ey >> K >> M;
  while (M--) {
    int D; cin >> D;
    vector<pii> v;
    for (int i = 0; i < D; ++i) {
      int x, y; cin >> x >> y;
      v.emplace_back(x, y);
    }
    for (int i = 1; i < D; ++i) {
      auto [x1, y1] = v[i - 1];
      auto [x2, y2] = v[i];
      if (x1 == x2) {
        int sy = min(y1, y2), ey = max(y1, y2);
        for (int y = sy; y <= ey; ++y) B[x1][y] = 1;
      } else {
        int sx = min(x1, x2), ex = max(x1, x2);
        for (int x = sx; x <= ex; ++x) B[x][y1] = 1;
      }
    }
  }

  memset(cdist, 0x3f, sizeof(cdist));
  using T = tuple<int, int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  cdist[sx][sy] = 1; pq.push({1, sx, sy});

  while (!pq.empty()) {
    auto [d, x, y] = pq.top(); pq.pop();
    if (cdist[x][y] < d) continue;
    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 1 || nx > N || ny < 1 || ny > N) continue;
      int nd = d + (B[nx][ny] ? K : 1);
      if (cdist[nx][ny] > nd) {
        cdist[nx][ny] = nd;
        from[nx][ny] = {x, y};
        pq.push({nd, nx, ny});
      }
    }
  }

  cout << cdist[ex][ey] << '\n';
  vector<pii> path, path2;
  for (pii cur = {ex, ey}; cur != make_pair(sx, sy); cur = from[cur.first][cur.second]) {
    path.push_back(cur);
  }
  path.push_back({sx, sy});
  reverse(path.begin(), path.end());

  path2.push_back({sx, sy});
  for (int i = 1; i < path.size() - 1; ++i) {
    auto [x1, y1] = path[i - 1];
    auto [x2, y2] = path[i + 1];
    if (x1 != x2 && y1 != y2) path2.push_back(path[i]);
  }
  path2.push_back({ex, ey});

  cout << path2.size() << ' ';
  for (const auto& [x, y] : path2) cout << x << ' ' << y << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
