#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
ll a[MAX + 1], d[6][MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  for (int i = 1; i <= n; i++) {
    d[0][i] = d[0][i - 1] + a[i];
    d[1][i] = max({d[0][i - 1], d[1][i - 1]});
    d[2][i] = max({d[0][i - 1], d[1][i - 1], d[2][i - 1]}) + a[i];
    d[3][i] = max({d[0][i - 1], d[1][i - 1], d[2][i - 1], d[3][i - 1]});
    d[4][i] = max({d[0][i - 1], d[1][i - 1], d[2][i - 1], d[3][i - 1], d[4][i - 1]}) + a[i];
    d[5][i] = max({d[0][i - 1], d[1][i - 1], d[2][i - 1], d[3][i - 1], d[4][i - 1], d[5][i - 1]});
  }

  cout << max({d[0][n], d[1][n], d[2][n], d[3][n], d[4][n], d[5][n]}) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
