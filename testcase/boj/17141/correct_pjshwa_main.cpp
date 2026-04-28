#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, INF = 1e9 + 7;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int board[MAX][MAX];
bool vis[MAX][MAX];

int main() {
  fast_io();

  int n, m; cin >> n >> m;
  vector<pii> virus;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> board[i][j];
    if (board[i][j] == 2) virus.push_back({i, j});
  }

  int ans = INF;
  for (int state = 1; state < (1 << virus.size()); state++) {
    if (__builtin_popcount(state) != m) continue;
    queue<tii> q;
    memset(vis, 0, sizeof(vis));

    for (int i = 0; i < virus.size(); i++) {
      if (state & (1 << i)) {
        auto [vi, vj] = virus[i];
        vis[vi][vj] = true;
        q.push({vi, vj, 0});
      }
    }

    int x = 0;
    while (!q.empty()) {
      auto [cx, cy, d] = q.front(); q.pop();
      x = max(x, d);

      for (int i = 0; i < 4; i++) {
        int nx = cx + dx[i], ny = cy + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        if (vis[nx][ny] || board[nx][ny] == 1) continue;
        vis[nx][ny] = true;
        q.push({nx, ny, d + 1});
      }
    }

    bool able = true;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
      if (board[i][j] != 1 && !vis[i][j]) able = false;
    }
    if (able) ans = min(ans, x);
  }

  cout << (ans == INF ? -1 : ans) << '\n';
}
