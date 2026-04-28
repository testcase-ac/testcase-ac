#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll dist(ll px, ll py, ll qx, ll qy) {
  return (px - qx) * (px - qx) + (py - qy) * (py - qy);
}

void solve() {
  ll r;
  cin >> r;

  ll mdist = 0, mx = -1;
  for (ll x = 1;; x++) {
    if ((r - 1) * (r - 1) + x * x >= r * r) break;
    ll cdist = dist(0, -r, x, r - 1);
    if (cdist > mdist) {
      mdist = cdist;
      mx = x;
    }
  }

  cout << mx << ' ' << r - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
