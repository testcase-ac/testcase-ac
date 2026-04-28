#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

const int MAX = 50;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX * MAX + 1][MAX][MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> board[i];

  queue<tuple<int, int, int>> q;
  if (board[0][0] == '0') {
    q.push({1, 0, 0});
    vis[1][0][0] = true;
  }
  else {
    q.push({0, 0, 0});
    vis[0][0][0] = true;
  }

  while (!q.empty()) {
    auto [z, x, y] = q.front();
    q.pop();

    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

      if (board[nx][ny] == '0' && z < MAX * MAX) {
        if (vis[z + 1][nx][ny]) continue;
        vis[z + 1][nx][ny] = true;
        q.push({z + 1, nx, ny});
      }
      else {
        if (vis[z][nx][ny]) continue;
        vis[z][nx][ny] = true;
        q.push({z, nx, ny});
      }
    }
  }

  for (int i = 0; i <= MAX * MAX; ++i) {
    if (vis[i][n - 1][n - 1]) {
      cout << i << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
