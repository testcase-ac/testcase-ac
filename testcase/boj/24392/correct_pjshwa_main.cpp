#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 1e9 + 7;
int board[MAX][MAX], d[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> board[i][j];
    }
  }

  for (int j = 0; j < m; j++) if (board[0][j] == 1) d[0][j] = 1;

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] == 0) continue;

      d[i][j] = (d[i][j] + d[i - 1][j]) % MOD;
      if (j > 0) d[i][j] = (d[i][j] + d[i - 1][j - 1]) % MOD;
      if (j < m - 1) d[i][j] = (d[i][j] + d[i - 1][j + 1]) % MOD;
    }
  }

  int ans = 0;
  for (int j = 0; j < m; j++) {
    ans = (ans + d[n - 1][j]) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
