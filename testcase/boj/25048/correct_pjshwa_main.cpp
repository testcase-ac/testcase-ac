#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300, MAXV = 1e5;
const ll INF = 1e18;
ll a[MAX + 1], b[MAX + 1];
ll d[MAX + 1][MAXV + 1];

void solve() {
  int n, m;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i] >> b[i], a[i] -= 2;
  cin >> m;

  for (int i = 0; i <= n; i++) fill(d[i], d[i] + MAXV + 1, INF);
  d[0][0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int v = 0; v <= MAXV; v++) {
      d[i][v] = d[i - 1][v];
      if (v >= a[i]) d[i][v] = min(d[i][v], d[i - 1][v - a[i]] + b[i]);
    }
  }

  ll ans = d[n][m - 1];
  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
