#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 10][MAX + 10];
bool vis[MAX + 2][MAX];
int n, m;

void dfs(int i, int j) {
  vis[i][j] = 1;
  for (int k = 0; k < 4; k++) {
    int x = i + dx[k], y = j + dy[k];
    if (x < 0 || x > n + 1 || y < 0 || y > m - 1 || vis[x][y] || board[x][y] == '1') continue;
    dfs(x, y);
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> board[i];
  dfs(0, 0);
  cout << (vis[n + 1][0] ? "YES\n" : "NO\n");
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
