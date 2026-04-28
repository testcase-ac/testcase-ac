#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 30;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
int vis[MAX][MAX];
int n, m, cnt, total, ans;

bool oob(int i, int j) {
  return i < 0 || i >= n || j < 0 || j >= m;
}

void mark(int i, int j) {
  vis[i][j] = 1;
  ++cnt;
}

void unmark(int i, int j) {
  vis[i][j] = 0;
  --cnt;
}

void dfs(int i, int j, int d, int mov) {
  mark(i, j);
  if (cnt == total) {
    ans = min(ans, mov);
  }
  else {
    int ni = i + dx[d], nj = j + dy[d];
    if (oob(ni, nj) || vis[ni][nj] || board[ni][nj] == '*') {
      for (int nd = 0; nd < 4; ++nd) {
        if (nd == d) continue;
        ni = i + dx[nd], nj = j + dy[nd];
        if (oob(ni, nj) || vis[ni][nj] || board[ni][nj] == '*') continue;
        dfs(ni, nj, nd, mov + 1);
      }
    }
    else dfs(ni, nj, d, mov);
  }
  unmark(i, j);
}

int tc;
void solve() {
  cout << "Case " << ++tc << ": ";

  for (int i = 0; i < n; ++i) cin >> board[i];
  memset(vis, 0, sizeof(vis));

  total = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (board[i][j] == '.') ++total;
  if (total == 1) return cout << "0\n", void();

  ans = n * m + 1;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (board[i][j] == '*') continue;
    for (int d = 0; d < 4; ++d) dfs(i, j, d, 1);
  }

  if (ans == n * m + 1) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> n >> m) solve();
}
