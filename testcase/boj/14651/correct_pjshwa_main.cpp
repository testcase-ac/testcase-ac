#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 9;
int d[3][MAX];

void solve() {
  int n;
  cin >> n;

  d[1][0] = d[2][0] = 1;
  for (int i = 1; i < n; i++) {
    d[0][i] = d[0][i - 1];
    d[1][i] = d[1][i - 1];
    d[2][i] = d[2][i - 1];

    d[0][i] = (d[0][i] + d[2][i - 1]) % MOD;
    d[1][i] = (d[1][i] + d[0][i - 1]) % MOD;
    d[2][i] = (d[2][i] + d[1][i - 1]) % MOD;

    d[0][i] = (d[0][i] + d[1][i - 1]) % MOD;
    d[1][i] = (d[1][i] + d[2][i - 1]) % MOD;
    d[2][i] = (d[2][i] + d[0][i - 1]) % MOD;
  }

  cout << d[0][n - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
