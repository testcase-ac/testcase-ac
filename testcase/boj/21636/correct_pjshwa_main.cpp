#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll d[20][20];

ll C(ll n, ll k) {
  ll res = 1;
  for (int i = 0; i < k; i++) {
    res *= n - i;
    res /= i + 1;
  }
  return res;
}

void solve() {
  int n, k;
  cin >> n >> k;

  d[0][0] = 1;
  for (int t = 1; t <= n; t++) for (int s = 0; s < n; s++) for (int j = 0; s + t * j <= n; j++) {
    d[t][s + t * j] += d[t - 1][s] * C(k + j - 1, j);
  }

  ll ans = 0;
  for (int t = 1; t <= n; t++) ans += d[t][n];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
