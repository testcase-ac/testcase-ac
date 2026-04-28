#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5, MOD = 1e9 + 7;
int d[5][MAX];

void solve() {
  int n;
  cin >> n;

  for (int j = 0; j < 5; j++) d[j][0] = 1;
  for (int i = 1; i < n; i++) {
    d[0][i] = (d[0][i] + d[1][i - 1]) % MOD;
    d[0][i] = (d[0][i] + d[2][i - 1]) % MOD;
    d[0][i] = (d[0][i] + d[3][i - 1]) % MOD;
    d[0][i] = (d[0][i] + d[4][i - 1]) % MOD;

    d[1][i] = (d[1][i] + d[0][i - 1]) % MOD;
    d[1][i] = (d[1][i] + d[3][i - 1]) % MOD;
    d[1][i] = (d[1][i] + d[4][i - 1]) % MOD;

    d[2][i] = (d[2][i] + d[0][i - 1]) % MOD;
    d[2][i] = (d[2][i] + d[4][i - 1]) % MOD;

    d[3][i] = (d[3][i] + d[0][i - 1]) % MOD;
    d[3][i] = (d[3][i] + d[1][i - 1]) % MOD;

    d[4][i] = (d[4][i] + d[0][i - 1]) % MOD;
    d[4][i] = (d[4][i] + d[1][i - 1]) % MOD;
    d[4][i] = (d[4][i] + d[2][i - 1]) % MOD;
  }

  int ans = 0;
  for (int j = 0; j < 5; j++) ans = (ans + d[j][n - 1]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
