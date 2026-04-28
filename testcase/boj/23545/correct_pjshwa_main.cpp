#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
char board[MAX + 1][MAX + 1];
bool vis[MAX + 1][MAX + 1];
int n, m, k, cc;

void dfs(int i, int j, int l) {
  cc++;
  vis[i][j] = true;
  for (int k = 0; k < 4; k++) {
    int x = i + dx[k], y = j + dy[k];
    if (x < l || x >= n || y < 0 || y >= m) continue;
    if (vis[x][y] || board[x][y] == '#') continue;
    dfs(x, y, l);
  }
}

bool check(int l) {
  int cnt = 0;
  memset(vis, false, sizeof(vis));
  for (int i = l; i < n; i++) for (int j = 0; j < m; j++) {
    if (vis[i][j] || board[i][j] == '#') continue;
    cc = 0;
    dfs(i, j, l);
    cnt = max(cnt, cc);
  }
  return cnt >= k;
}

void solve() {
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) cin >> board[i];

  int l = 0, r = n;
  while (l < r) {
    int m = (l + r) / 2;
    if (check(m)) l = m + 1;
    else r = m;
  }

  if (l == 0) l = -1;
  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
