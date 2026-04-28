#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, INF = 1e9 + 7;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
char board[MAX + 1][MAX + 1];
bool vis[4][2][2][MAX][MAX];
int sdist[4][2][2][MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  vector<pii> cs;
  int si, sj;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'S') si = i, sj = j;
    if (board[i][j] == 'C') cs.push_back({i, j});
  }
  auto [c0i, c0j] = cs[0];
  auto [c1i, c1j] = cs[1];

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) for (int k = 0; k < 4; k++) {
    sdist[k][0][0][i][j] = sdist[k][0][1][i][j] = INF;
    sdist[k][1][0][i][j] = sdist[k][1][1][i][j] = INF;
  }

  queue<tuple<int, int, int, int, int, int>> q;
  for (int k = 0; k < 4; k++) q.push({k, 0, 0, si, sj, 0}), vis[k][0][0][si][sj] = 1;

  while (!q.empty()) {
    auto [dir, c0vis, c1vis, i, j, dist] = q.front();
    q.pop();

    c0vis |= (i == c0i && j == c0j);
    c1vis |= (i == c1i && j == c1j);
    sdist[dir][c0vis][c1vis][i][j] = min(dist, sdist[dir][c0vis][c1vis][i][j]);

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
      if (board[ni][nj] == '#') continue;
      if (vis[k][c0vis][c1vis][ni][nj]) continue;
      if (k == dir) continue;

      q.push({k, c0vis, c1vis, ni, nj, dist + 1});
      vis[k][c0vis][c1vis][ni][nj] = 1;
    }
  }

  int ans = INF;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) for (int k = 0; k < 4; k++) {
    ans = min(ans, sdist[k][1][1][i][j]);
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
