#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll b, c; int N; cin >> b >> c >> N;

  map<pair<ll, ll>, int> uL, uR;
  for (int i = 0; i < N; ++i) {
    ll x, y; cin >> x >> y;
    if (x == b || y >= c) continue;

    ll e1 = c - y, e2 = (x - b) * (x - b);
    ll g = gcd(e1, e2);
    auto u = make_pair(e1 / g, e2 / g);
    if (x < b) ++uL[u];
    else ++uR[u];
  }

  int ans = 0;
  for (auto& [_, cnt] : uL) ans = max(ans, cnt);
  for (auto& [_, cnt] : uR) ans = max(ans, cnt);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
