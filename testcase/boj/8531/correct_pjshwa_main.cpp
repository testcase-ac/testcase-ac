#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  for (ll n = 1; n <= 100; ++n) for (ll a = 1; a <= 1000; ++a) {
    cout << "n = " << n << ", a = " << a << '\n';

    set<pair<ll, ll>> v;
    for (ll denom = 1; denom <= n; ++denom) {
      ll nom = (a + 1) * denom / (n * n);
      if (a * denom <= nom * n * n) {
        ll g = gcd(nom, denom);
        v.emplace(nom / g, denom / g);
      }
    }

    for (auto [nom, denom] : v) {
      cout << nom << '/' << denom << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
