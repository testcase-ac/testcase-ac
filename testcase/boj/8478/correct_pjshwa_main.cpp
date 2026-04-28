#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, m; cin >> n >> m;
  n %= (2 * m);

  vector<ll> D(2 * m);
  D[0] = D[2] = (1 % m);
  for (ll i = 3; i < 2 * m; ++i) {
    ll add = i % 2 ? -1 : 1;
    D[i] = (i * D[i - 1] + m + add) % m;
  }

  ll ans = D[n] * D[n] % m;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
