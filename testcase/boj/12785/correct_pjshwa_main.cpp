#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 1e6 + 7;
ll d[MAX + 1][MAX + 1];

ll C(int n, int k) {
  if (d[n][k] != -1) return d[n][k];

  if (n < 0 || k < 0 || n < k) return d[n][k] = 0;
  if (k == 0 || n == k) return d[n][k] = 1;
  return d[n][k] = (C(n - 1, k - 1) + C(n - 1, k)) % MOD;
}

void solve() {
  int w, h, x, y;
  cin >> w >> h >> x >> y;
  w--; h--; x--; y--;
  w -= x; h -= y;

  memset(d, -1, sizeof(d));
  ll ans = C(x + y, x) * C(w + h, h) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
