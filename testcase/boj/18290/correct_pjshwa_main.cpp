#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
bool vis[MAX][MAX];
int board[MAX][MAX];
int n, m, k;
int ans = -1e9, sum;

void dfs(int i, int j, int ck) {
  if (k == ck) {
    ans = max(ans, sum);
    return;
  }
  else if (i == n && j == 0) return;

  j == m - 1 ? dfs(i + 1, 0, ck) : dfs(i, j + 1, ck);

  if (i > 0 && vis[i - 1][j]) return;
  if (j > 0 && vis[i][j - 1]) return;
  vis[i][j] = 1;
  sum += board[i][j];
  j == m - 1 ? dfs(i + 1, 0, ck + 1) : dfs(i, j + 1, ck + 1);
  sum -= board[i][j];
  vis[i][j] = 0;
}

void solve() {
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];
  dfs(0, 0, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
