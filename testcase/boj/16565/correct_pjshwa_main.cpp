#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e4 + 7;
int C[60][60];

void solve() {
  int n;
  cin >> n;

  int ans = 0;
  for (int i = 1; i <= 13; i++) {
    if (4 * i > n) break;

    int cur = (C[13][i] * C[52 - 4 * i][n - 4 * i]) % MOD;
    if (i & 1) ans = (ans + cur) % MOD;
    else ans = (ans - cur + MOD) % MOD;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  C[0][0] = 1;
  for (int i = 1; i < 60; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
