#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 7;

// d[i][j][k][l]: Solved to problem l
// i: Whether C solved anything
// j: Whether B solved problem l
// k: Solve count of A mod K
int d[2][2][10][MAX + 1];

void solve() {
  int n, k;
  cin >> n >> k;

  d[0][0][0][0] = 1;

  if (k == 0) {
    for (int i = 1; i <= n; i++) {
      d[0][1][0][i] = (d[0][1][0][i] + d[0][0][0][i - 1]) % MOD;
      d[1][1][0][i] = (d[1][1][0][i] + d[1][0][0][i - 1]) % MOD;
      d[1][0][0][i] = (d[1][0][0][i] + d[0][0][0][i - 1]) % MOD;
      d[1][0][0][i] = (d[1][0][0][i] + d[0][1][0][i - 1]) % MOD;
      d[1][0][0][i] = (d[1][0][0][i] + d[1][0][0][i - 1]) % MOD;
      d[1][0][0][i] = (d[1][0][0][i] + d[1][1][0][i - 1]) % MOD;
    }
  }
  else {
    for (int i = 1; i <= n; i++) {
      // A has solved problem i
      for (int j = 1; j < k; j++) {
        d[0][0][j][i] = (d[0][0][j - 1][i - 1] + d[0][1][j - 1][i - 1]) % MOD;
        d[1][0][j][i] = (d[1][0][j - 1][i - 1] + d[1][1][j - 1][i - 1]) % MOD;
      }
      d[0][0][0][i] = (d[0][0][k - 1][i - 1] + d[0][1][k - 1][i - 1]) % MOD;
      d[1][0][0][i] = (d[1][0][k - 1][i - 1] + d[1][1][k - 1][i - 1]) % MOD;

      // B has solved problem i
      for (int j = 0; j < k; j++) {
        d[0][1][j][i] = (d[0][1][j][i] + d[0][0][j][i - 1]) % MOD;
        d[1][1][j][i] = (d[1][1][j][i] + d[1][0][j][i - 1]) % MOD;
      }

      // C has solved problem i
      for (int j = 0; j < k; j++) {
        d[1][0][j][i] = (d[1][0][j][i] + d[0][0][j][i - 1]) % MOD;
        d[1][0][j][i] = (d[1][0][j][i] + d[0][1][j][i - 1]) % MOD;
        d[1][0][j][i] = (d[1][0][j][i] + d[1][0][j][i - 1]) % MOD;
        d[1][0][j][i] = (d[1][0][j][i] + d[1][1][j][i - 1]) % MOD;
      }
    }
  }

  int ans = 0;
  ans = (ans + d[1][0][0][n]) % MOD;
  ans = (ans + d[1][1][0][n]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
