#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const ll INF = 1e18;
ll a[MAX + 1][MAX + 1], d[MAX + 1][MAX + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
  
  ll omax = 0;
  for (int j = 1; j <= m; j++) omax = max(omax, a[1][j]);
  for (int j = 1; j <= m; j++) d[1][j] = omax + (omax - a[1][j]);
  for (int i = 2; i <= n; i++) for (int j = 1; j <= m; j++) d[i][j] = INF;

  for (int i = 2; i <= n; i++) {
    ll omax = 0, omin = INF;
    for (int j = 1; j <= m; j++) {
      omax = max(omax, a[i][j]);
      omin = min(omin, a[i][j]);
    }

    for (int p = 1; p <= m; p++) for (int j = 1; j <= m; j++) {
      ll pre = a[i - 1][p], cur = a[i][j];
      ll val = min(
        abs(pre - omin) + (omax - omin) + abs(cur - omax),
        abs(pre - omax) + (omax - omin) + abs(cur - omin)
      );
      d[i][j] = min(d[i][j], d[i - 1][p] + val);
    }
  }

  ll ans = INF;
  for (int j = 1; j <= m; j++) ans = min(ans, d[n][j]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
