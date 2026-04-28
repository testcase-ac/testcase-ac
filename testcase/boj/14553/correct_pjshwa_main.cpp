#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 1e9 + 9;
ll d[MAX];

void solve() {
  int n;
  cin >> n;

  d[0] = 0, d[1] = 1, d[2] = 4, d[3] = 12;
  for (int i = 4; i <= n; i++) {
    d[i] = (4 * d[i - 1] + 2 * d[i - 3] + d[i - 4]) % MOD;
    for (int j = 0; j < 3; j++) d[i] = (d[i] + MOD - d[i - 2]) % MOD;
  }

  cout << d[n] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
