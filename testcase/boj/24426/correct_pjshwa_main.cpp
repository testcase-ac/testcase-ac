#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
ll a[MAX + 1][MAX + 1], d[MAX + 1][MAX + 1];

void solve() {
  int n, r, c;
  cin >> n;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> a[i][j];
  cin >> r >> c;

  for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) {
    d[i][j] = max(d[i - 1][j], d[i][j - 1]) + a[i][j];
  }
  ll im = d[r][c];
  memset(d, 0, sizeof(d));
  for (int i = r; i <= n; i++) for (int j = c; j <= n; j++) {
    d[i][j] = max(d[i - 1][j], d[i][j - 1]) + a[i][j];
  }
  cout << im + d[n][n] - a[r][c] << ' ';

  memset(d, 0, sizeof(d));
  if (r == 1) {
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
      if (i == r && j >= c) continue;
      if (i == r + 1 && j >= c) d[i][j] = d[i][j - 1] + a[i][j];
      else d[i][j] = max(d[i - 1][j], d[i][j - 1]) + a[i][j];
    }
  }
  else if (c == 1) {
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
      if (i >= r && j == c) continue;
      if (i >= r && j == c + 1) d[i][j] = d[i - 1][j] + a[i][j];
      else d[i][j] = max(d[i - 1][j], d[i][j - 1]) + a[i][j];
    }
  }
  else {
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
      if (i == r && j == c) continue;
      if (i == r + 1 && j == c) d[i][j] = d[i][j - 1] + a[i][j];
      else if (i == r && j == c + 1) d[i][j] = d[i - 1][j] + a[i][j];
      else d[i][j] = max(d[i - 1][j], d[i][j - 1]) + a[i][j];
    }
  }
  cout << d[n][n] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
