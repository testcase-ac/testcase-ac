#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int d[MAX + 1][MAX + 1][2];

void solve() {
  int n, k;
  cin >> n >> k;

  d[1][0][0] = d[1][0][1] = 1;
  for (int i = 2; i <= n; i++) for (int j = 0; j <= k; j++) {
    d[i][j][0] = d[i - 1][j][0] + d[i - 1][j][1];
    d[i][j][1] = d[i - 1][j][0];
    if (j) d[i][j][1] += d[i - 1][j - 1][1];
  }

  cout << d[n][k][0] + d[n][k][1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
