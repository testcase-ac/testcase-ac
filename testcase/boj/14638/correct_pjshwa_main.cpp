#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 256;
const ll INF = 1e18;
ll a[MAX + 10], d[MAX + 10][MAX + 10];
ll r(int u, int k) {
  if (d[u][k] != -1) return d[u][k];

  ll res = 0;
  if (k == 1) for (int i = 0; i < u; i++) res += a[i] * (i - u) * (i - u);
  else {
    res = INF;
    for (int i = 0; i < u; i++) {
      ll cur = r(i, k - 1);
      if (cur == INF) continue;

      for (int j = i + 1; j < u; j++) {
        ll mul = min(j - i, u - j);
        cur += a[j] * mul * mul;
      }
      res = min(res, cur);
    }
  }
  return d[u][k] = res;
}

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    int r, p;
    cin >> r >> p;
    a[r] = p;
  }

  memset(d, -1, sizeof(d));
  ll ans = INF;
  for (int i = 0; i < MAX; i++) {
    ll cur = r(i, k);
    if (cur == INF) continue;

    for (int j = i + 1; j < MAX; j++) {
      cur += a[j] * (j - i) * (j - i);
    }
    ans = min(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
