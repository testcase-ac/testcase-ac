#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, m;
ll d[11][2001];

void solve() {
  cin >> n >> m;

  memset(d, 0, sizeof(d));
  for (int j = 1; j <= m; j++) d[1][j] = j;

  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= m; j++) d[i][j] += d[i - 1][j / 2];
    for (int j = 1; j <= m; j++) d[i][j] += d[i][j - 1];
  }

  cout << d[n][m] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
