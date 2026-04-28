#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 9;
int d[MAX + 1][2];

void solve() {
  int n; cin >> n;
  cout << d[n][1] << ' ' << d[n][0] << '\n';
}

int main() {
  fast_io();

  d[0][0] = 1;
  for (int i = 1; i <= MAX; i++) {
    for (int v = 1; v <= 3; v++) {
      if (i - v < 0) continue;
      for (int p = 0; p < 2; p++) {
        d[i][p] = (d[i][p] + d[i - v][1 - p]) % MOD;
      }
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
