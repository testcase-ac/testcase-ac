#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, m, board[MAX][MAX], g[MAX][MAX];
int parent[MAX];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void dfs(int i, int j, int c) {
  g[i][j] = c;
  for (int k = 0; k < 4; k++) {
    int nx = i + dx[k], ny = j + dy[k];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
    if (g[nx][ny] == 0 && board[nx][ny] == 1) dfs(nx, ny, c);
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];

  int cc = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (g[i][j] == 0 && board[i][j] == 1) dfs(i, j, ++cc);
  }

  for (int i = 1; i <= cc; i++) parent[i] = i;

  vector<tii> edges;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (g[i][j] == 0) continue;

    int cgroup = g[i][j];
    for (int x = i - 1; x >= 0; x--) {
      if (g[x][j] == 0) continue;
      if (g[x][j] == cgroup) break;
      edges.emplace_back(i - x - 1, g[x][j], g[i][j]);
      break;
    }
    for (int y = j - 1; y >= 0; y--) {
      if (g[i][y] == 0) continue;
      if (g[i][y] == cgroup) break;
      edges.emplace_back(j - y - 1, g[i][y], g[i][j]);
      break;
    }
  }
  sort(edges.begin(), edges.end());

  ll ans = 0, uc = 0;
  for (auto [w, x, y] : edges) {
    if (Find(x) == Find(y)) continue;
    if (w < 2) continue;
    ans += w;
    uc++;
    Union(x, y);
  }

  if (uc == cc - 1) cout << ans << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
