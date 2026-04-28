#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

double d[21][81];

void solve() {
  double W, L, D;
  cin >> W >> L >> D;

  d[0][40] = 1;
  for (int i = 1; i <= 20; i++) for (int j = 20; j <= 60; j++) {
    d[i][j] = d[i - 1][j - 1] * W + d[i - 1][j + 1] * L + d[i - 1][j] * D;
  }

  double ans[9] = {0};
  for (int j = 20; j <= 60; j++) ans[j / 10] += d[20][j];
  for (int u = 2; u <= 6; u++) cout << fixed << setprecision(8) << ans[u] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
