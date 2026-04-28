#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3000, MOD = 1e9 + 7;
char board[MAX + 1][MAX + 1];
int d[3][MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (i) d[0][i][j] = (d[0][i][j] + d[0][i - 1][j]) % MOD;
    if (j) d[0][i][j] = (d[0][i][j] + d[0][i][j - 1]) % MOD;
    if (i && j) d[0][i][j] = (d[0][i][j] + MOD - d[0][i - 1][j - 1]) % MOD;
    if (board[i][j] == 'E') d[0][i][j] = (d[0][i][j] + 1) % MOD;
  }
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (i) d[1][i][j] = (d[1][i][j] + d[1][i - 1][j]) % MOD;
    if (j) d[1][i][j] = (d[1][i][j] + d[1][i][j - 1]) % MOD;
    if (i && j) d[1][i][j] = (d[1][i][j] + MOD - d[1][i - 1][j - 1]) % MOD;
    if (board[i][j] == 'S') {
      if (i) d[1][i][j] = (d[1][i][j] + d[0][i - 1][j]) % MOD;
      if (j) d[1][i][j] = (d[1][i][j] + d[0][i][j - 1]) % MOD;
      if (i && j) d[1][i][j] = (d[1][i][j] + MOD - d[0][i - 1][j - 1]) % MOD;
    }
  }
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (i) d[2][i][j] = (d[2][i][j] + d[2][i - 1][j]) % MOD;
    if (j) d[2][i][j] = (d[2][i][j] + d[2][i][j - 1]) % MOD;
    if (i && j) d[2][i][j] = (d[2][i][j] + MOD - d[2][i - 1][j - 1]) % MOD;
    if (board[i][j] == 'M') {
      if (i) d[2][i][j] = (d[2][i][j] + d[1][i - 1][j]) % MOD;
      if (j) d[2][i][j] = (d[2][i][j] + d[1][i][j - 1]) % MOD;
      if (i && j) d[2][i][j] = (d[2][i][j] + MOD - d[1][i - 1][j - 1]) % MOD;
    }
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    // cout << "i: " << i << " j: " << j << " d[0][i][j]: " << d[0][i][j] << endl;
    // cout << "i: " << i << " j: " << j << " d[1][i][j]: " << d[1][i][j] << endl;
    // cout << "i: " << i << " j: " << j << " d[2][i][j]: " << d[2][i][j] << endl;
  }

  cout << d[2][n - 1][m - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
