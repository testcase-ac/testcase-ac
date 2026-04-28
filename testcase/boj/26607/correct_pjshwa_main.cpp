#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 80, MAXV = 16000;
int a[MAX + 1];
bool d[MAX + 1][MAX + 1][MAXV + 1];

void solve() {
  ll n, k, x;
  cin >> n >> k >> x;
  for (int i = 1; i <= n; i++) cin >> a[i] >> a[i];

  d[0][0][0] = true;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= k; j++) {
      for (int v = 0; v <= MAXV; v++) d[i][j][v] = d[i - 1][j][v];
    }

    for (int j = 0; j < k; j++) {
      for (int v = 0; v <= MAXV; v++) {
        if (d[i - 1][j][v] && v + a[i] <= MAXV) d[i][j + 1][v + a[i]] = true;
      }
    }
  }

  ll ans = 0;
  for (int v = 0; v <= MAXV; v++) {
    if (!d[n][k][v]) continue;

    ans = max(ans, v * (k * x - v));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
