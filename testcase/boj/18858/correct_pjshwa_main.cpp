#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 998244353;
int d[2][101][1000];

void solve() {
  int n, m;
  cin >> n >> m;

  if (n == 1) return cout << m << '\n', void();
  if (n == 2) return cout << m * m << '\n', void();

  for (int i = 1; i <= m; i++) for (int j = 1; j <= m; j++) {
    if (i < j) d[1][j][1]++;
    else d[0][j][1]++;
  }
  for (int i = 2; i < n; i++) for (int j = 1; j <= m; j++) for (int k = 1; k <= m; k++) {
    if (j > k) d[0][k][i] = (d[0][k][i] + d[0][j][i - 1]) % MOD;
    else if (j < k) {
      d[1][k][i] = (d[1][k][i] + d[0][j][i - 1]) % MOD;
      d[1][k][i] = (d[1][k][i] + d[1][j][i - 1]) % MOD;
    }
    else {
      d[0][k][i] = (d[0][k][i] + d[0][j][i - 1]) % MOD;
      d[0][k][i] = (d[0][k][i] + d[1][j][i - 1]) % MOD;
    }
  }

  int ans = 0;
  for (int j = 1; j <= m; j++) ans = (ans + d[0][j][n - 1]) % MOD;
  for (int j = 1; j <= m; j++) ans = (ans + d[1][j][n - 1]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
