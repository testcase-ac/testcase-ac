#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300, MAXV = 150;
const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
bool vis[MAX + 1][MAX + 1][MAXV + 1];

void solve() {
  int N, M, K, t;
  cin >> N >> M >> K >> t;

  queue<tuple<int, int, int>> q;
  while (M--) {
    int x, y;
    cin >> x >> y;
    q.push({x, y, 0});
    vis[x][y][0] = true;
  }

  while (!q.empty()) {
    auto [x, y, d] = q.front(); q.pop();

    for (int k = 0; k < 8; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 1 || nx > N || ny < 1 || ny > N) continue;

      int nd = d + 1;
      if (nd > MAXV) nd -= 2;

      if (vis[nx][ny][nd]) continue;
      q.push({nx, ny, nd});
      vis[nx][ny][nd] = true;
    }
  }

  if (t > MAXV) t = MAXV - (t & 1);

  bool f = false;
  while (K--) {
    int x, y;
    cin >> x >> y;
    f |= vis[x][y][t];
  }

  if (f) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
