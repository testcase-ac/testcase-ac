#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;

void solve() {
  int n;
  cin >> n;

  map<pair<ll, ll>, int> t;
  for (int i = 0; i < n; i++) {
    ll ai, bi, ci;
    cin >> ai >> bi >> ci;

    ll g = __gcd(ai, bi);
    ai /= g, bi /= g;
    t[{ai, bi}]++;
  }

  ll c1 = 0, c2 = 0, c3 = 0;
  for (auto& [k, v] : t) {
    c3 = (c3 + c2 * v) % MOD;
    c2 = (c2 + c1 * v) % MOD;
    c1 = (c1 + v) % MOD;
  }

  cout << c3 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
