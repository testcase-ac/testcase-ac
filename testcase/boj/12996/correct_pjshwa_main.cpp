#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, MOD = 1e9 + 7;
int d[MAX + 1][MAX + 1][MAX + 1][MAX + 1];

void solve() {
  int n, a, b, c;
  cin >> n >> a >> b >> c;

  d[0][0][0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = a; j >= 0; j--) {
      for (int k = b; k >= 0; k--) {
        for (int l = c; l >= 0; l--) {
          if (j > 0) d[i][j][k][l] = (d[i][j][k][l] + d[i - 1][j - 1][k][l]) % MOD;
          if (k > 0) d[i][j][k][l] = (d[i][j][k][l] + d[i - 1][j][k - 1][l]) % MOD;
          if (l > 0) d[i][j][k][l] = (d[i][j][k][l] + d[i - 1][j][k][l - 1]) % MOD;
          if (j > 0 && k > 0) d[i][j][k][l] = (d[i][j][k][l] + d[i - 1][j - 1][k - 1][l]) % MOD;
          if (j > 0 && l > 0) d[i][j][k][l] = (d[i][j][k][l] + d[i - 1][j - 1][k][l - 1]) % MOD;
          if (k > 0 && l > 0) d[i][j][k][l] = (d[i][j][k][l] + d[i - 1][j][k - 1][l - 1]) % MOD;
          if (j > 0 && k > 0 && l > 0) d[i][j][k][l] = (d[i][j][k][l] + d[i - 1][j - 1][k - 1][l - 1]) % MOD;
        }
      }
    }
  }
  cout << d[n][a][b][c] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
