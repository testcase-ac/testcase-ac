#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int board[MAX][MAX];
bool vis[MAX][MAX];
int n, m;

pair<int, int> bfs(int si, int sj) {
  memset(vis, 0, sizeof(vis));
  queue<tii> q;
  q.push({si, sj, 0});
  vis[si][sj] = true;

  int sv = board[si][sj], ev = -1, md = -1;
  while (!q.empty()) {
    auto [i, j, d] = q.front();
    q.pop();

    if (md == d) ev = max(ev, board[i][j]);
    else if (md < d) {
      md = d;
      ev = board[i][j];
    }

    if (i > 0 && board[i - 1][j] != 0 && !vis[i - 1][j]) vis[i - 1][j] = true, q.push({i - 1, j, d + 1});
    if (i < n - 1 && board[i + 1][j] != 0 && !vis[i + 1][j]) vis[i + 1][j] = true, q.push({i + 1, j, d + 1});
    if (j > 0 && board[i][j - 1] != 0 && !vis[i][j - 1]) vis[i][j - 1] = true, q.push({i, j - 1, d + 1});
    if (j < m - 1 && board[i][j + 1] != 0 && !vis[i][j + 1]) vis[i][j + 1] = true, q.push({i, j + 1, d + 1});
  }

  if (ev == -1) return {0, 0};
  else return {sv + ev, md};
}

int main() {
  fast_io();

  cin >> n >> m;
  assert(1 <= n && n <= 100);
  assert(1 <= m && m <= 100);

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    cin >> board[i][j];
    assert(0 <= board[i][j] && board[i][j] <= 9);
  }

  int ans = 0, md = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] != 0) {
      auto [cv, cd] = bfs(i, j);
      if (cd > md) {
        md = cd;
        ans = cv;
      }
      else if (cd == md) ans = max(ans, cv);
    }
  }
  cout << ans << '\n';
}
