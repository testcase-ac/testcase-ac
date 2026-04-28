#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int rec(ll x, ll y, ll w, ll l) {
  if (l == 0) return 0;
  ll h = w / 2, q = w / 4;
  if (x >= h && y >= h) return rec(x - h, y - h, w / 2, l - 1);
  if (x >= q && x < 3 * q && y >= q && y < 3 * q) return rec(x - q, y - q, w / 2, l - 1);
  if (x >= h) return (rec(y, w - x - 1, w / 2, l - 1) + 3) % 4;
  if (y >= h) return (rec(w - y - 1, x, w / 2, l - 1) + 1) % 4;
  return rec(x, y, w / 2, l - 1);
}

void solve() {
  ll x, y, l = 0, w = 2; cin >> x >> y;
  while (x >= w || y >= w) w *= 2, ++l;
  cout << rec(x, y, w, l) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
