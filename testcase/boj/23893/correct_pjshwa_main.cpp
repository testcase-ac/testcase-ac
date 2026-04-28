#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n, p, k;
  cin >> n >> p >> k;

  map<ll, ll> t;
  for (int i = 0; i < n; i++) {
    ll x, u = 1;
    cin >> x;
    u = (u * x) % p;
    u = (u * x) % p;
    u = (u * x) % p;
    u = (u + (p - (k * x) % p)) % p;
    t[u]++;
  }

  ll ans = 0;
  for (auto &[u, cnt] : t) {
    ans += cnt * (cnt - 1) / 2;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
