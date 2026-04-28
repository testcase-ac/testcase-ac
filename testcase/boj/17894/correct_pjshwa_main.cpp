#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 100;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX + 1][MAX + 1];

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> board[i];
    for (int j = 0; j < m; j++) vis[i][j] = board[i][j] == '#';
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (vis[i][j]) continue;

    board[i][j] = 'E';
    vis[i][j] = true;
    for (int k = 0; k < 4; k++) {
      int nx = i + dx[k], ny = j + dy[k];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
      vis[nx][ny] = true;
    }
  }

  for (int i = 0; i < n; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
