#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, MOD = 1e9 + 9;
int d[MAX + 1][MAX + 1];

void solve() {
  int m, n; cin >> m >> n;
  cout << d[n][m] << '\n';
}

int main() {
  fast_io();

  for (int i = 0; i <= MAX; i++) memset(d[i], 0, sizeof(d[i]));
  d[0][0] = 1;

  for (int i = 1; i <= MAX; i++) {
    for (int u : {1, 2, 3}) {
      for (int j = u; j <= MAX; j++) {
        d[i][j] += d[i - 1][j - u];
        d[i][j] %= MOD;
      }
    }
  }

  for (int i = 1; i <= MAX; i++) for (int j = 0; j <= MAX; j++) {
    d[i][j] += d[i - 1][j];
    d[i][j] %= MOD;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
