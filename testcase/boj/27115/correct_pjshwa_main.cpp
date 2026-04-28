#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
vector<pii> D[MAX + 1];
bool vis[MAX + 1][MAX + 1];

void solve() {
  int N, M, K;
  cin >> N >> M >> K;

  while (K--) {
    int y, x, p;
    cin >> y >> x >> p;
    D[p].push_back({y, x});
  }

  queue<pii> q;
  for (int v = MAX; v >= 1; v--) {
    for (auto& [y, x] : D[v]) {
      if (vis[y][x]) continue;
      vis[y][x] = true;
      q.push({y, x});
    }

    queue<pii> nq;
    while (!q.empty()) {
      auto [y, x] = q.front(); q.pop();

      for (int i = 0; i < 4; i++) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 1 || ny > N || nx < 1 || nx > M) continue;
        if (vis[ny][nx]) continue;
        vis[ny][nx] = true;
        nq.push({ny, nx});
      }
    }

    q = nq;
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    if (vis[i][j]) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
