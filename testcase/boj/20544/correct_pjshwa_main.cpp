#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 1e9 + 7;
int d[2][8][MAX + 10];

void solve() {
  int n;
  cin >> n;

  d[0][0][1] = 1;
  for (int i = 2; i <= n; i++) {
    for (int u : {0, 1}) {
      d[u][0][i] = (d[u][0][i] + d[u][0][i - 1]) % MOD;
      d[u][0][i] = (d[u][0][i] + d[u][3][i - 1]) % MOD;
      d[u][0][i] = (d[u][0][i] + d[u][6][i - 1]) % MOD;
      d[u][1][i] = (d[u][1][i] + d[u][0][i - 1]) % MOD;
      d[u][1][i] = (d[u][1][i] + d[u][3][i - 1]) % MOD;
      d[u][1][i] = (d[u][1][i] + d[u][6][i - 1]) % MOD;
      d[1][2][i] = (d[1][2][i] + d[u][0][i - 1]) % MOD;
      d[1][2][i] = (d[1][2][i] + d[u][3][i - 1]) % MOD;
      d[1][2][i] = (d[1][2][i] + d[u][6][i - 1]) % MOD;

      d[u][3][i] = (d[u][3][i] + d[u][1][i - 1]) % MOD;
      d[u][3][i] = (d[u][3][i] + d[u][4][i - 1]) % MOD;
      d[u][3][i] = (d[u][3][i] + d[u][7][i - 1]) % MOD;
      d[u][4][i] = (d[u][4][i] + d[u][1][i - 1]) % MOD;
      // d[u][4][i] = (d[u][4][i] + d[u][4][i - 1]) % MOD;
      // d[u][4][i] = (d[u][4][i] + d[u][7][i - 1]) % MOD;
      d[1][5][i] = (d[1][5][i] + d[u][1][i - 1]) % MOD;
      // d[1][5][i] = (d[1][5][i] + d[u][4][i - 1]) % MOD;
      // d[1][5][i] = (d[1][5][i] + d[u][7][i - 1]) % MOD;

      d[u][6][i] = (d[u][6][i] + d[u][2][i - 1]) % MOD;
      d[u][6][i] = (d[u][6][i] + d[u][5][i - 1]) % MOD;
      d[u][7][i] = (d[u][7][i] + d[u][2][i - 1]) % MOD;
      // d[u][7][i] = (d[u][7][i] + d[u][5][i - 1]) % MOD;
    }
  }

  int ans = 0;
  for (int i = 0; i < 8; i++) ans = (ans + d[1][i][n]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
