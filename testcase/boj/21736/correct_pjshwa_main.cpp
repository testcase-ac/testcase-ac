#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 600;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  queue<pii> q;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'I') q.push({i, j}), vis[i][j] = true;
  }

  int ans = 0;
  while (!q.empty()) {
    auto [ci, cj] = q.front();
    q.pop();

    if (board[ci][cj] == 'P') ans++;

    for (int i = 0; i < 4; i++) {
      int ni = ci + dx[i], nj = cj + dy[i];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m || vis[ni][nj]) continue;
      if (board[ni][nj] != 'X') {
        q.push({ni, nj});
        vis[ni][nj] = true;
      }
    }
  }

  if (ans) cout << ans << '\n';
  else cout << "TT\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
