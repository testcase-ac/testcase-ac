#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int board[MAX + 1][MAX + 1], d[MAX + 1][MAX + 1];
int n, m;

void solve() {
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> board[i][j];
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    if (board[i][j] == 0) d[i][j] = 0;
    else d[i][j] = min(d[i - 1][j], min(d[i][j - 1], d[i - 1][j - 1])) + 1;
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) ans = max(ans, d[i][j]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    solve();
  }
}
