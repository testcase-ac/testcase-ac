#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1000, MOD = 1e9 + 9;
int d[MAX + 1][MAX + 1];

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m; cin >> n >> m;
  cout << d[n][m] << '\n';
}

int main() {
  fast_io();

  d[0][0] = 1;
  for (int v = 0; v <= MAX; v++) for (int i = 1; i <= MAX; i++) {
    for (int u = 1; u <= 3; u++) {
      if (v < u) break;
      d[v][i] = (d[v][i] + d[v - u][i - 1]) % MOD;
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
