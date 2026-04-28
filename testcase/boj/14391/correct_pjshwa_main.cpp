#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX];
int w, n, m;
int c;

int get_type(int i, int j) {
  int p = i * m + j;
  if (w & (1 << p)) return 1;
  else return 0;
}

void dfs(int i, int j, int t) {
  vis[i][j] = 1;
  c += board[i][j] - '0';

  if (t) {
    int x = i, y = j + 1;
    if (y < m && !vis[x][y] && get_type(x, y) == t) c *= 10, dfs(x, y, t);
  }
  else {
    int x = i + 1, y = j;
    if (x < n && !vis[x][y] && get_type(x, y) == t) c *= 10, dfs(x, y, t);
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  int ans = 0;
  for (w = 0; w < (1 << (n * m)); w++) {
    int cur = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
      if (vis[i][j]) continue;
      c = 0;
      dfs(i, j, get_type(i, j));
      cur += c;
    }

    ans = max(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
