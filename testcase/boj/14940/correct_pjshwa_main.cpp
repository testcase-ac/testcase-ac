#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int cdist[MAX][MAX];
bool vis[MAX][MAX], ban[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;

  queue<tii> q;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    int x;
    cin >> x;
    if (x == 0) ban[i][j] = 1;
    if (x == 2) {
      q.push({i, j, 0});
      vis[i][j] = 1;
    }
  }

  while (!q.empty()) {
    auto [x, y, c] = q.front();
    q.pop();

    cdist[x][y] = c;
    for (int k = 0; k < 4; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m || vis[nx][ny] || ban[nx][ny]) continue;
      q.push({nx, ny, c + 1});
      vis[nx][ny] = 1;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (ban[i][j]) cout << "0 ";
      else if (!vis[i][j]) cout << "-1 ";
      else cout << cdist[i][j] << " ";
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
