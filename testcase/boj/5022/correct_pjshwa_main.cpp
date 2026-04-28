#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 101, INF = 1e9 + 7;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
pii vis[MAX][MAX];
bool cpath[MAX][MAX];
int n, m;
int si, sj, ei, ej;

int bfs_backtrack() {
  queue<tii> q;
  q.push({si, sj, 0});
  vis[si][sj] = {-1, -1};

  while (!q.empty()) {
    auto [i, j, cnt] = q.front();
    q.pop();

    if (i == ei && j == ej) {
      cpath[i][j] = true;
      auto [ni, nj] = vis[i][j];
      while (ni != -1) {
        cpath[ni][nj] = true;
        tie(ni, nj) = vis[ni][nj];
      }
      return cnt;
    }

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k];
      int nj = j + dy[k];

      if (ni < 0 || ni > n || nj < 0 || nj > m) continue;
      if (vis[ni][nj] != pii(-2, -2)) continue;
      vis[ni][nj] = {i, j};
      q.push({ni, nj, cnt + 1});
    }
  }
  return INF;
}

int bfs() {
  queue<tii> q;
  q.push({si, sj, 0});
  cpath[si][sj] = true;

  while (!q.empty()) {
    auto [i, j, cnt] = q.front();
    q.pop();

    if (i == ei && j == ej) return cnt;

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k];
      int nj = j + dy[k];

      if (ni < 0 || ni > n || nj < 0 || nj > m) continue;
      if (cpath[ni][nj]) continue;
      cpath[ni][nj] = true;
      q.push({ni, nj, cnt + 1});
    }
  }
  return INF;
}

void init() {
  memset(cpath, false, sizeof(cpath));
  for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) vis[i][j] = {-2, -2};
}

void solve() {
  pii a1, a2, b1, b2;
  cin >> n >> m;
  cin >> a1.first >> a1.second >> a2.first >> a2.second;
  cin >> b1.first >> b1.second >> b2.first >> b2.second;

  int ans = INF, cur;

  init();
  tie(si, sj) = a1;
  tie(ei, ej) = a2;
  vis[b1.first][b1.second] = vis[b2.first][b2.second] = {-3, -3};
  cur = bfs_backtrack();
  tie(si, sj) = b1;
  tie(ei, ej) = b2;
  ans = min(ans, bfs() + cur);

  init();
  tie(si, sj) = b1;
  tie(ei, ej) = b2;
  vis[a1.first][a1.second] = vis[a2.first][a2.second] = {-3, -3};
  cur = bfs_backtrack();
  tie(si, sj) = a1;
  tie(ei, ej) = a2;
  ans = min(ans, bfs() + cur);

  if (ans >= INF) cout << "IMPOSSIBLE\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
