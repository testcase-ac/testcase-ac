#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, a, b; cin >> n >> a >> b;
  vector<ll> V;
  for (int i = 0; i < 2 * n; i++) V.push_back(a + i * b);

  for (int i = 0; i < n; i++) {
    ll u = V[2 * i], v = V[2 * i + 1];
    if (__gcd(u, v) != 1) return cout << "No\n", void();
  }

  cout << "Yes\n";
  for (int i = 0; i < n; i++) {
    ll u = V[2 * i], v = V[2 * i + 1];
    cout << u << " " << v << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
