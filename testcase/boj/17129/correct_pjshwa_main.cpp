#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3000;
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  queue<tii> q;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == '2') q.push({i, j, 0}), vis[i][j] = true;
  }

  while (!q.empty()) {
    auto [x, y, cnt] = q.front();
    q.pop();

    if (board[x][y] == '3' || board[x][y] == '4' || board[x][y] == '5') {
      cout << "TAK\n" << cnt << '\n';
      return;
    }

    if (x - 1 >= 0 && board[x - 1][y] != '1' && !vis[x - 1][y]) {
      q.push({x - 1, y, cnt + 1}), vis[x - 1][y] = true;
    }
    if (x + 1 < n && board[x + 1][y] != '1' && !vis[x + 1][y]) {
      q.push({x + 1, y, cnt + 1}), vis[x + 1][y] = true;
    }
    if (y - 1 >= 0 && board[x][y - 1] != '1' && !vis[x][y - 1]) {
      q.push({x, y - 1, cnt + 1}), vis[x][y - 1] = true;
    }
    if (y + 1 < m && board[x][y + 1] != '1' && !vis[x][y + 1]) {
      q.push({x, y + 1, cnt + 1}), vis[x][y + 1] = true;
    }
  }

  cout << "NIE\n";
}


int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
