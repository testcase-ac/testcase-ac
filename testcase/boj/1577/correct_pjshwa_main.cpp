#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
ll d[MAX + 1][MAX + 1];
bool rh[MAX + 1][MAX + 1], rv[MAX + 1][MAX + 1];

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  while (k--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    pii u = {a, b}, v = {c, d};
    if (u > v) swap(u, v);

    if (u.first == v.first) rh[v.first][v.second] = 1;
    else rv[v.first][v.second] = 1;
  }

  d[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    if (rv[i][0]) continue;
    d[i][0] += d[i - 1][0];
  }
  for (int j = 1; j <= m; j++) {
    if (rh[0][j]) continue;
    d[0][j] += d[0][j - 1];
  }
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    if (!rv[i][j]) d[i][j] += d[i - 1][j];
    if (!rh[i][j]) d[i][j] += d[i][j - 1];
  }

  cout << d[n][m] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
