#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

const int MAXN = 1e4;
int G[MAXN];

void solve() {
  int p, n; cin >> p >> n;
  for (int i = 0; i < p; ++i) ++G[lpow(i, n, p)];

  vector<pii> V;
  for (int i = 0; i < p; ++i) {
    if (G[i]) V.emplace_back(i, G[i]);
  }

  ll ans = 0;
  for (auto& [k1, v1] : V) for (auto& [k2, v2] : V) {
    ans += (ll)v1 * v2 * G[(k1 + k2) % p];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
