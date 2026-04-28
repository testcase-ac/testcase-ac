#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
int cdist[MAXN + 1][MAXN + 1];

void solve() {
  int N, M, R, C; cin >> N >> M >> R >> C;
  vector<tuple<int, int, int>> rooms;
  while (R--) {
    int a, b, p; cin >> a >> b >> p;
    rooms.emplace_back(a, b, p);
  }

  memset(cdist, 0x3f, sizeof(cdist));
  queue<pii> Q;
  while (C--) {
    int c, d; cin >> c >> d;
    cdist[c][d] = 0; Q.emplace(c, d);
  }
  while (!Q.empty()) {
    auto [x, y] = Q.front(); Q.pop();
    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
      if (cdist[nx][ny] > cdist[x][y] + 1) {
        cdist[nx][ny] = cdist[x][y] + 1;
        Q.emplace(nx, ny);
      }
    }
  }

  int ans = INF;
  for (auto& [x, y, p] : rooms) {
    ans = min(ans, cdist[x][y] * p);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
