#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20, INF = 1e9 + 7;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
int c1x, c1y, c2x, c2y;
int d, ans = INF;
int n, m;

bool oob(int x, int y) {
  return x < 0 || x >= n || y < 0 || y >= m;
}

void dfs() {
  d++;

  if (d <= 10) {
    for (int k = 0; k < 4; k++) {
      auto [n1x, n1y] = pii(c1x + dx[k], c1y + dy[k]);
      auto [n2x, n2y] = pii(c2x + dx[k], c2y + dy[k]);

      if (oob(n1x, n1y) ^ oob(n2x, n2y)) ans = min(ans, d);
      else if (!oob(n1x, n1y) && !oob(n2x, n2y)) {
        if (board[n1x][n1y] == '#') n1x -= dx[k], n1y -= dy[k];
        if (board[n2x][n2y] == '#') n2x -= dx[k], n2y -= dy[k];

        int oc1x = c1x, oc1y = c1y, oc2x = c2x, oc2y = c2y;
        c1x = n1x, c1y = n1y, c2x = n2x, c2y = n2y;
        dfs();
        c1x = oc1x, c1y = oc1y, c2x = oc2x, c2y = oc2y;
      }
    }
  }

  d--;
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  bool f = false;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'o') {
      if (!f) {
        tie(c1x, c1y) = {i, j};
        f = true;
      }
      else tie(c2x, c2y) = {i, j};
    }
  }

  dfs();
  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
